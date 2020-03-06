#pragma once

#include <iostream>
#include <vector>

namespace game {
    using PlayerID = int;

    class Player{
        public:
            Player();
        private:
            PlayerID id;
            std::string name;
            // std::vector<game::Elements> elements;
    };
}