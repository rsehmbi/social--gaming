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

using user::UserType;

struct CurrentGameState {
    UserVariables perPlayer;
    UserVariables perAudience;
    UserVariables gameVariables;
};

class GameSessionInterface
{
    public:
        virtual void sessionBroadCast(const std::string& text) = 0;

        virtual void msgUsersOfType(UserType userType, const std::string& text) = 0;

        virtual void msgUser(int id, const std::string& text) = 0;

        // TODO: need to implement these inside the game Session.
        // virtual void setGlobalTimer() = 0;

        // virtual void setTimer(UserType userType, int id) = 0;
};