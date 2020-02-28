#pragma once

#include <GameSessionInterface.h>

class GameSession : private GameSessionInterface{

    public:
        //Initialized by the session manager, session manager will pass 
        //in game type argument containing game information
        GameSession(SessionID id);
        
        //Entry point for session manager to pass execution to a game session.
        //Session manager passes the messages from clients of this session to processGameTurn
        //and lets the game execute its next turn. Function should use this turn to perform
        //all its game logic that can be performed until further input from players are required.
        //use sessionBroadCast and msgConnection to send msgs to clients
        MessageBatch processGameTurn(const MessageBatch& incomingMsgs);

        //remove user from game session
        void disconnect(const ConnectionID& cid);
        
        //add user to game session
        void connect(const ConnectionID& cid);

    private:

        SessionID sessionID;

        std::unordered_set<ConnectionID> connections;

        MessageBatch outMsgs;

        void sessionBroadCast(const std::string& text);

        void msgConnection(const ConnectionID& target, const std::string& msg);
};

