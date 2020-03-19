#include <GameSession.h>

#include <glog/logging.h>
#include <sstream>
#include <iostream>


static const std::string MSG_NO_ROOM_FOR_PLAYER = "No room for a new player";

//Initialized by the session manager, session manager will pass 
//in game type argument containing game information
GameSession::GameSession(SessionID id, ConnectionID ownerConnectionId, const Constants& _constants, 
    const GameRules& _rules, GameState _gameState, Configurations _configurations)
    :   sessionID{id},
        owner{User {"", -1, ownerConnectionId, UserType::Owner} },
        constants(_constants), 
        rules(_rules),
        configurations(_configurations),
        gameState(_gameState)
{   
    sessionUsers.push_back(owner);
    LOG(INFO) << "Session created with id: " << sessionID;
}

MessageBatch
GameSession::processGameTurn(const MessageBatch& inMsgs, std::shared_ptr<Interpreter> interpreter){
    MessageBatch msgBuffer;
    interpreter->setCurrentGameSession(this);

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
        [](auto&& msg) { return std::move(msg); }
    );
    
    outMsgs.clear();

    //-----------end of perform game turn-------
    return msgBuffer;
}

// This is a function to test the communication from interpreter to game session.
// TODO: needs to be refactored.
void 
GameSession::messageAllClients() {
    msgConnectionsOfType(UserType::Audience, "This is an audience");
    msgConnectionsOfType(UserType::Player, "This is a player");
    msgConnectionsOfType(UserType::Owner, "This is the owner");
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
GameSession::connect(const ConnectionID& cid, const NewUserType newUserType){
    if (cid == owner.getConnectionID())
        return ;

    int maxPlayersAllowed = configurations.getMaxNoOfPlayers();

    // Find the userType of the new connection.
    UserType userType = UserType::Player;
    if (newUserType == NewUserType::Default) {
        // Max players allowed. if the number of session users is more than
        // this they will be added as audience.
        userType = getUserCountWithType(UserType::Player) < maxPlayersAllowed 
            ? UserType::Player : UserType::Audience;
    } else if (newUserType == NewUserType::Player) {
        int playerCount = getUserCountWithType(UserType::Player);
        if (playerCount < maxPlayersAllowed ){
            userType = UserType::Player;
        } else {
            // if no new player can be added, show an error message to the user.
            msgConnection(cid, MSG_NO_ROOM_FOR_PLAYER);
            return ;
        } 
    } else if (newUserType == NewUserType::Audience) {
        userType = UserType::Audience;
    }
            
    User user {"", getUserCountWithType(userType) + 1, cid, userType};
    sessionUsers.push_back(user);
    
    // Send messgae to owner informing a new user in session.
    std::string userTypeStr = UserType::Player == userType ? "Player" : "Audience";
    std::ostringstream stream;
    stream << userTypeStr << " joined with id " << cid;
    msgConnection(owner.getConnectionID(), stream.str());

    // Send message to client to inform connection status
    stream.str("");
    stream.clear();
    stream << "Connected to session: " << sessionID << "\n";
    msgConnection(cid, stream.str());
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