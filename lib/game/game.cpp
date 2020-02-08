#include "game.h"

game::Game(game::Configurations configurations, game::GameRules gameRules, game::Constants constants, game::GameState gameState) 
    : m_configurations(configs), m_gameRules(rules), m_constants(consts), m_gameState(state)
{
}

game::Configurations game::getConfigurations() {
    return this->m_configurations;
}

game::GameRules game::getRules() {
    return this->m_rules;
}

game::Constants game::getConstants() {
    return this->m_constants;
}

game::GameState game::getGameState() {
    return this->m_state;
}