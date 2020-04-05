#pragma once

#include <string>
#include <unordered_set>

#include <Server.h>
#include <User.h>

using networking::Server;
using networking::Connection;
using networking::Message;
using networking::MessageBatch;
using networking::SessionID;
using networking::ConnectionID;
using networking::UserIdType;

using user::UserType;
using game::Variable;
using game::VariableType;

using MessageText = std::string;
using Time = long;

struct RunningGameState {

    std::shared_ptr<Variables> variables;

    // Map from User id to incoming message from that user.
    std::unordered_map<UserIdType, MessageText> messageMap;

    // when a new game starts it starts by creating a copy of the default
    // variables. This constructor initializes all the necessay top level variables.
    RunningGameState(){
        variables = std::make_shared<Variables>();
        messageMap = std::unordered_map<UserIdType, MessageText>();
        
        auto players = std::make_shared<Variable>();
        auto audiences = std::make_shared<Variable>();

        players->varType = VariableType::ListType;
        audiences->varType = VariableType::ListType;
    
        variables->createVariable("players", players);
        variables->createVariable("audiences", players);
    }
};

class GameSessionInterface
{
    public:
        virtual void sessionBroadCast(const std::string& text) = 0;

        virtual void msgUsersOfType(UserType userType, const std::string& text) = 0;

        virtual void msgUser(UserIdType id, const std::string& text) = 0;

        virtual void setGlobalTimeout() = 0;

        virtual void setTimeout(UserIdType id, Time delay) = 0;
};