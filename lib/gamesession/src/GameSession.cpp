#include <GameSession.h>

#include <glog/logging.h>
#include <sstream>
#include <iostream>



//Initialized by the session manager, session manager will pass 
//in game type argument containing game information
GameSession::GameSession(SessionID id, ConnectionID ownerConnectionId, const Constants& _constants, 
    const GameRules& _rules, GameState _gameState, Configurations _configurations)
    :   sessionID{id},
        owner{User {"", -1, ownerConnectionId, UserType::Owner} },
        constants(_constants), 
        rules(_rules),
        gameState(_gameState),
        configurations(_configurations)
{   
    sessionUsers.push_back(owner);
    LOG(INFO) << "Session created with id: " << sessionID;
}

MessageBatch
GameSession::processGameTurn(const MessageBatch& inMsgs){
    MessageBatch msgBuffer;

    //-----------perform game turn-------

    //FOR TESTING: send msg back to each player
    for(auto& msg : inMsgs){
        std::ostringstream out;
        out << msg.connection.id << "> " << msg.text << "\n";
        msgBuffer.push_back({{msg.connection.id}, out.str()});
    }

    // send all the incoming messages out in the current tick.
    std::transform(std::make_move_iterator(outMsgs.begin()), 
        std::make_move_iterator(outMsgs.end()),
        std::back_inserter(msgBuffer), 
        [](auto&& msg) { return msg; });
    outMsgs.clear();

    //-----------end of perform game turn-------
    return msgBuffer;
}

void 
GameSession::sessionBroadCast(const std::string& text){
    for (const User& user : sessionUsers){
        msgConnection(user.getConnectionID(), text);
    }
}

void
GameSession::msgConnectionsOfType(UserType userType, const std::string& text){
    if (userType == UserType::Owner){
        msgConnection(owner.getConnectionID(), text);
    } else {
        for (const User& user : sessionUsers){
            if (user.getUserType() == userType)
                msgConnection(user.getConnectionID(), text);
        }
    }
}

void 
GameSession::msgConnection(const ConnectionID& target, const std::string& msg){
    LOG(INFO) << "Sending message to connection: " << target;
    outMsgs.push_back({{target}, msg});
}

void 
GameSession::disconnect(const ConnectionID& cid){
    sessionUsers.erase(std::remove_if(sessionUsers.begin(), sessionUsers.end(), 
        [&cid] (User& user) {return user.getConnectionID() == cid;})
    );
}

void 
GameSession::connect(const ConnectionID& cid){
    if (cid == owner.getConnectionID())
        return ;

    // Max players allowed. if the number of session users is more than
    // this they will be added as audience.
    int maxPlayersAllowed = configurations.getMaxNoOfPlayers();

    UserType userType = getUserCountWithType(UserType::Player) < maxPlayersAllowed 
        ? UserType::Player : UserType::Audience;

    User user {"", getUserCountWithType(userType) + 1, cid, userType};
    sessionUsers.push_back(user);

    // Send messgae to owner informing a new user in session.
    std::string userTypeStr = UserType::Player == userType ? "Player" : "Audience";
    std::ostringstream stream;
    stream << userTypeStr << " joined with id " << cid;
    std::string message = stream.str();
    msgConnection(owner.getConnectionID(), stream.str());
    LOG(INFO) << stream.str();
}

std::vector<User> 
GameSession::getPlayers() {
    return getUsersWithType(UserType::Player);
}

std::vector<User> 
GameSession::getAudience() {
    return getUsersWithType(UserType::Audience);
}

std::vector<User> 
GameSession::getUsersWithType(const UserType& userType) {
    std::vector<User> users;

    std::copy_if(sessionUsers.begin(), sessionUsers.end(), std::back_inserter(users),
        [&userType](User& user) { return user.getUserType() == userType;}
    );
    
    return users;
}

int 
GameSession::getUserCountWithType(const UserType& userType){
    return std::count_if(sessionUsers.begin(), sessionUsers.end(), 
        [&userType ](User& user) { return user.getUserType() == userType; }
    );
}