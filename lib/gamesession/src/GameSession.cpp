#include <GameSession.h>

#include <sstream>
#include <iostream>



//Initialized by the session manager, session manager will pass 
//in game type argument containing game information

GameSession::GameSession(SessionID id, ConnectionID ownerConnectionId) 
    :   sessionID{id},
        owner{User {"", -1, ownerConnectionId, UserType::Owner} } {
}

MessageBatch 
GameSession::processGameTurn(const MessageBatch& inMsgs){
    outMsgs.clear();
    //-----------perform game turn-------

    //FOR TESTING: send msg back to each player
    for(auto& msg : inMsgs){
        std::ostringstream out;
        out << msg.connection.id << "> " << msg.text << "\n";
        outMsgs.push_back({msg.connection.id, out.str()});
    }
    //broadcast test
    sessionBroadCast("broadcast test: " + sessionID + "\n");

    //-----------end of perform game turn-------
    return outMsgs;
}

void 
GameSession::sessionBroadCast(const std::string& text){
    for(const auto& connectionid : connections){
        msgConnection(connectionid, text);
    }
}

void 
GameSession::msgConnection(const ConnectionID& target, const std::string& msg){
    outMsgs.push_back({target, msg});
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

    UserType userType = getUserCountWithType(UserType::Player) < maxPlayersAllowed 
        ? UserType::Player : UserType::Audience;
    User user {"", getUserCountWithType(userType) + 1, cid, userType};
    sessionUsers.push_back(user);
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