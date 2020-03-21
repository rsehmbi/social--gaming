#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "Messages.h"
#include "UserVariables.h"

using game::Variables;
using game::UserVariables;

namespace game{
    
struct GameState {
    Variables gameVariables;
    Variables perPlayer;
    Variables perAudience;
};

}

#endif