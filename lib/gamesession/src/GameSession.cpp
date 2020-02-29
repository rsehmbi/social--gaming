#include <GameSession.h>

#include <sstream>
#include <iostream>

using user::User;
using user::UserType;

//Initialized by the session manager, session manager will pass 
//in game type argument containing game information

GameSession::GameSession(SessionID id, ConnectionID ownerConnectionId) 
    :   sessionID{id},
        owner{User {"", -1, ownerConnectionId, UserType::Owner} } {
}

MessageBatch GameSession::processGameTurn(const MessageBatch& inMsgs){
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

void GameSession::sessionBroadCast(const std::string& text){
    for(const auto& connectionid : connections){
        msgConnection(connectionid, text);
    }
}

void GameSession::msgConnection(const ConnectionID& target, const std::string& msg){
    outMsgs.push_back({target, msg});
}

void GameSession::disconnect(const ConnectionID& cid){
    connections.erase(cid);
}

void GameSession::connect(const ConnectionID& cid){
    connections.insert(cid);
}

