#include "game.h"

game::game(game::configurations configs, game::gameRules rules, game::constants consts, game::gameState state) 
    : m_configurations(configs), m_rules(rules), m_constants(consts), m_state(state)
{
};