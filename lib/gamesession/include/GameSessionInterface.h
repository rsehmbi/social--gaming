#pragma once

#include <string>
#include <Server.h>
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
        virtual void messageAllClients() = 0;
};