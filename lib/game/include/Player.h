#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

namespace game{
class Player{
    public:
        Player();
    private:
        int id;
        std::string name;
        // std::vector<game::Elements> elements;
};
}

#endif