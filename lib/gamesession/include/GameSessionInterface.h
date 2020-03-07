#pragma once

#include <string>
#include <Server.h>
#include <sstream>
#include <unordered_set>

using networking::Server;
using networking::Connection;
using networking::Message;
using networking::MessageBatch;
using networking::SessionID;
using networking::ConnectionID;

class GameSessionInterface
{
    public:
        virtual ~GameSessionInterface(){};
        virtual void sessionBroadCast(const std::string& text) = 0;
        virtual void msgConnection(const ConnectionID& target, const std::string& msg) = 0;
};