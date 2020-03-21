#pragma once

#include <unordered_set>
#include <vector>
#include <Server.h>
#include <User.h>
#include <Game.h>
#include <interpreter.h>
#include <GameSessionInterface.h>

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
using game::UserVariables;

using interpreter::Interpreter;

enum NewUserType {
    Default,
    Player,
    Audience
};

class GameSession : public GameSessionInterface {

    public:
        //Initialized by the session manager, session manager will pass 
        //in game type argument containing game information
        GameSession(SessionID id, ConnectionID ownerConnectionId, const Constants& _constants, 
            const GameRules& _rules, const GameState& _gameState, Configurations _configurations);
        
        //Entry point for session manager to pass execution to a game session.
        //Session manager passes the messages from clients of this session to processGameTurn
        //and lets the game execute its next turn. Function should use this turn to perform
        //all its game logic that can be performed until further input from players are required.
        //use sessionBroadCast and msgConnection to send msgs to clients
        MessageBatch processGameTurn(const MessageBatch& incomingMsgs, std::shared_ptr<Interpreter> interpreter);

        // Send messgae to all the session users.
        void sessionBroadCast(const std::string& text); 

        // Send message to users of type provided by second param only.
        void msgUsersOfType(UserType userType, const std::string& text);

        //remove user from game session
        void disconnect(const ConnectionID& cid);
        
        //add user to game session
        void connect(const ConnectionID& cid, const NewUserType newUserType);

        // start the game if the conditions are met.
        void startGame(const ConnectionID& cid);

        // Filters the users that are players.
        std::vector<user::User> getPlayers();

    private:

        // ------- Game Data --------------------
        const Constants& constants;

        const GameRules& rules;

        Configurations configurations;

        GameState initialState;

        CurrentGameState currentState;
        // --------------------------------------


        // ------- Connections Data -------------
        bool gameStarted;

        SessionID sessionID;

        std::vector<user::User> sessionUsers;

        user::User owner;

        MessageBatch outMsgs;
        // --------------------------------------


        void msgConnection(const ConnectionID& target, const std::string& msg);  

        std::vector<User> getUsersWithType(const UserType& userType);

        std::vector<User> getAudience();

        int getUserCountWithType(const UserType& userType);

        // When a new user is added initialize the state for that user in perPlayer or 
        // perAudience based on the userType.
        void addUserToState(UserType userType, int userId);

        // create a buffer for player messages.

        // create and hold a timer to handle the timer rules

        // create an interpreter and send messages to the interpreter.

        // check if the messages are comming from the interpreter.
};