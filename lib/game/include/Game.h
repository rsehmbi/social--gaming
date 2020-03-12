#ifndef GAME_H
#define GAME_H

#include "json.hpp"

#include "Configurations.h"
#include "Constants.h"
#include "GameState.h"
#include "GameRules.h"

namespace game{
class Game{

public:

    Game();

    Game(Configurations& configurations, GameRules& gameRules, 
        Constants& constants, GameState& gameState);

    void setConfigurations(Configurations& configurations);

    Configurations getConfigurations() const;
    
    GameRules getGameRules();
    
    Constants getConstants();
    
    GameState getGameState();

private:
    
    Configurations m_configurations;

    GameRules m_gameRules;

    Constants m_constants;

    GameState m_gameState;
};
}

#endif