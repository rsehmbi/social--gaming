#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "Variables.h"
#include "Messages.h"
#include "UserVariables.h"

using game::Variables;

namespace game{
    
struct GameState {
    Variables gameVariables;
    Variables perPlayer;
    Variables perAudience;
};

}

#endif