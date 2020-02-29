#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "player.h"
#include "messages.h"
#include "json.hpp"

namespace game{
struct Update{
    //types of data to return
}

class GameState{
    public:
        // TODO : Remove default constructor once createGameState is done.
        GameState();
        GameState(const nlohmann::json& jsonVariables);
        Update getUpdate(); //prototype function to return only updated data through json
    private:
        //TODO: need function to check for updated data
        std::vector<game::Player> playerList;
        game::Message messages;
        game::Variables variables;

        game::Variables getJSONVariables(const nlohmann::json& jsonVariables);
};
}

#endif