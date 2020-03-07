#include "GameState.h"

using game::GameState;

GameState::GameState(){

    // TODO : implement constructor.
}

GameState::GameState(basic_json var, basic_json pPlayer, basic_json pAudience):
    variables(var), perPlayer(pPlayer){}