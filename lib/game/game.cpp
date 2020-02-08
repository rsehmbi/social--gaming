#include "game.h"

game::game(game::configurations configs, game::gameRules rules, game::constants consts, game::gameState state) 
    : m_configurations(configs), m_rules(rules), m_constants(consts), m_state(state)
{
}

game::configurations game::getConfigurations() {
    return this->m_configurations;
}

game::gameRules game::getRules() {
    return this->m_rules;
}

game::constants game::getConstants() {
    return this->m_constants;
}

game::gameState game::getGameState() {
    return this->m_state;
}