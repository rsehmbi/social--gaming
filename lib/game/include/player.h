#pragma once

#include <iostream>
#include <vector>
#include <GameSession.h>

namespace game {
    using PlayerID = int;

    class Player{
        public:
            Player();
            ConnectionID getConnectionID() {return connectionID;}; //needs work still

        private:
            PlayerID id;
            std::string name;
            // std::vector<game::Elements> elements;
            ConnectionID connectionID;

    };
}