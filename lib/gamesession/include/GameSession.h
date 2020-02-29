#pragma once

#include <Server.h>
#include <User.h>

#include <unordered_set>
#include <vector>

using networking::SessionID;
using networking::MessageBatch;
using networking::ConnectionID; 

class GameSession{

    public:
        //Initialized by the session manager, session manager will pass 
        //in game type argument containing game information
        GameSession(SessionID id, ConnectionID ownerConnectionId);
        
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

        std::vector<user::User> sessionUsers;

        user::User owner;

        MessageBatch outMsgs;

        void sessionBroadCast(const std::string& text);

        void msgConnection(const ConnectionID& target, const std::string& msg);
};