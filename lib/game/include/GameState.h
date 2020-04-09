#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "Messages.h"
#include "UserVariables.h"

using game::Variables;

namespace game{
    
struct GameState {
    std::shared_ptr<Variable> gameVariables;
    std::shared_ptr<Variable> perPlayer;
    std::shared_ptr<Variable> perAudience;
    std::shared_ptr<Variable> constants;
};
}

#endif