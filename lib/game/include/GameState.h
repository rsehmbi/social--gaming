#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "Messages.h"
#include "json.hpp"

using game::Variables;

namespace game{
struct Update{
    //content of new update to client
};

struct GameState{
    Variables variables;
    Variables perPlayer;
    Variables perAudience;
    Update newUpdate;
};

// class GameState{
//     public:
//         // TODO : Remove default constructor once createGameState is done.
//         GameState();
//         GameState(const basic_json& var, const basic_json& pPlayer, const basic_json& pAudience);
//         game::Variables getUpdate(); //prototype function to return only updated data through json
//     private:
//         //TODO: need function to check for updated data
//         game::Variables variables;
//         game::PerPlayer perPlayer;
//         game::PerAudience perAudience;
//         game::Messages messages;
        

//         // game::Variables getJSONVariables(const nlohmann::json& jsonVariables);
// };
}

#endif