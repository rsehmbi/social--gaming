#include "Game.h"
#include "GameRules.h"

using game::Game;
using game::Configurations;
using game::GameRules;
using game::Constants;
using game::GameState;

Game::Game()
{

}

Game::Game(Configurations configurations, GameRules gameRules, 
    Constants constants, GameState gameState)
    :   m_configurations(std::move(configurations)),
        m_gameRules(std::move(gameRules)),
        m_constants(std::move(constants)),
        m_gameState(std::move(gameState))
{
}

void 
Game::setConfigurations(Configurations& configurations) {
    m_configurations = std::move(configurations);
} 

Configurations 
Game::getConfigurations() const{
    return m_configurations;
}

GameRules&
Game::getGameRules() {
    return m_gameRules;
}

Constants&
Game::getConstants() {
    return m_constants;
}

GameState 
Game::getGameState() {
    return m_gameState;
}