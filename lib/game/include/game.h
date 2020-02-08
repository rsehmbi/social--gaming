#include <nlohmann/json.hpp>
#include "gameRules.h"

namespace game{
class game{

public:

    game(game::configurations configs, game::gameRules rules, game::constants consts, game::gameState state);

    game::configurationss getConfigurations();
    game::gameRules getRules();
    game::constants getConstants();
    game::gameState getGameState();

private:
    
    game::configurations m_configurations;

    game::gameRules m_rules;

    game::constants m_constants;

    game::gameState m_state;
};
}