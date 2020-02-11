#include <GameSession.h>

//Initialized by the session manager, session manager will pass 
//in game type argument containing game information

GameSession::GameSession(SessionID id) : 
        sessionID{id} {
}

//Entry point for session manager to pass execution to a game session.
//Session manager passes the messages from clients of this session to processGameTurn
//and lets the game execute its next turn. Function should use this turn to perform
//all its game logic that can be performed until further input from players are required.
//use mgrPtr->sessionBroadCast and mgrPtr->msgConnection to send msgs to clients
MessageBatch GameSession::processGameTurn(const MessageBatch& inMsgs){
    // void msgConnection(Message& message);
    // void sessionBroadCast(id, Message msg);
    MessageBatch outMsgs;
    //FOR TESTING: send msg back to each player.
    for(auto& msg : inMsgs){
        std::ostringstream out;
        out << msg.connection.id << "> " << msg.text << "\n";
        outMsgs.push_back({msg.connection.id, out.str()});
    }
    return outMsgs;
}

