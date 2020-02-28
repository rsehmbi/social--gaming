#include <GameSession.h>

//Initialized by the session manager, session manager will pass 
//in game type argument containing game information

GameSession::GameSession(SessionID id) : 
        sessionID{id} {
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
    sessionBroadCast("broadcast test\n");

    
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