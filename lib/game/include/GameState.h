#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "PerPlayer.h"
#include "Messages.h"
#include "json.hpp"

namespace game{
struct Update{
    //types of data to return
}

class GameState{
    public:
        // TODO : Remove default constructor once createGameState is done.
        GameState();
        GameState(const basic_json&, const basic_json&, const basic_json&);
        game::Variables getUpdate(); //prototype function to return only updated data through json
    private:
        //TODO: need function to check for updated data
        game::Variables variables;
        game::PerPlayer perPlayer;
        // game::PerAudience perAudience;
        game::Messages messages;
        

        // game::Variables getJSONVariables(const nlohmann::json& jsonVariables);
};
}

#endif