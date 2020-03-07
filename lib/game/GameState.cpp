#include "GameState.h"

using game::GameState;

GameState::GameState(){

    // TODO : implement constructor.
}

GameState::GameState(const basic_json& var, const basic_json& pPlayer, const basic_json& pAudience):
    variables{var}, perPlayer{pPlayer}, perAudience{pAudience}{}