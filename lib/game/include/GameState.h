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
        GameState(basic_json, basic_json, basic_json);
        game::Variables getUpdate(); //prototype function to return only updated data through json
    private:
        //TODO: need function to check for updated data
        game::Variables variables;
        std::vector<game::Player> perPlayer;

        game::Message messages;
        

        // game::Variables getJSONVariables(const nlohmann::json& jsonVariables);
};
}

#endif