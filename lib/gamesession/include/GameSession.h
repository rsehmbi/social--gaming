#pragma once

#include <string>
#include <Server.h>
#include <sstream>

using networking::Server;
using networking::Connection;
using networking::Message;
using networking::MessageBatch;
using networking::SessionID;
using networking::ConnectionID;

class GameSession {

    public:
        //Initialized by the session manager, session manager will pass 
        //in game type argument containing game information
        GameSession(SessionID id);
        
        //Entry point for session manager to pass execution to a game session.
        //Session manager passes the messages from clients of this session to processGameTurn
        //and lets the game execute its next turn. Function should use this turn to perform
        //all its game logic that can be performed until further input from players are required.
        //use mgrPtr->sessionBroadCast and mgrPtr->msgConnection to send msgs to clients
        MessageBatch processGameTurn(const MessageBatch& incomingMsgs);

    private:

        SessionID sessionID;
};

