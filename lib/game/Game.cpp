#include "Game.h"
#include "GameRules.h"

using namespace game;

Game::Game()
{

}

Game::Game(Configurations& configurations, GameRules& gameRules, 
    Constants& constants, GameState& gameState)
    :   m_configurations(std::move(configurations)),
        m_gameRules(std::move(gameRules)),
        m_constants(std::move(constants)),
        m_gameState(std::move(gameState))
{
}

Configurations 
Game::getConfigurations() {
    return m_configurations;
}

GameRules 
Game::getGameRules() {
    return m_gameRules;
}

Constants 
Game::getConstants() {
    return m_constants;
}

GameState 
Game::getGameState() {
    return m_gameState;
}