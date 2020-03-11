#pragma once

#include <unordered_set>
#include <vector>
#include <Server.h>
#include <User.h>
#include <Game.h>

using networking::SessionID;
using networking::MessageBatch;
using networking::ConnectionID; 

using user::User;
using user::UserType;
using game::Game;
using game::GameState;
using game::GameRules;
using game::Constants;
using game::Configurations;

class GameSession{

    public:
        //Initialized by the session manager, session manager will pass 
        //in game type argument containing game information
        GameSession(SessionID id, ConnectionID ownerConnectionId, const Constants& _constants, 
    const GameRules& _rules, GameState _gameState, Configurations _configurations);
        
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

        // Filters the users that are players.
        std::vector<user::User> getPlayers();

    private:

        SessionID sessionID;

        std::vector<user::User> sessionUsers;

        user::User owner;

        MessageBatch outMsgs;

        // Send messgae to all the session users.
        void sessionBroadCast(const std::string& text);

        // Send message to users of type provided by second param only.
        void msgConnectionsOfType(UserType userType, const std::string& text);

        void msgConnection(const ConnectionID& target, const std::string& msg);  

        std::vector<User> getUsersWithType(const UserType& userType);

        std::vector<User> getAudience();

        int getUserCountWithType(const UserType& userType);

        const Constants& constants;

        const GameRules& rules;

        Configurations configurations;

        GameState gameState;
};