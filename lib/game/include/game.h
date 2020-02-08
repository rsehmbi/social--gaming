#include <nlohmann/json.hpp>
#include "gameRules.h"

namespace game{
class Game{

public:

    Game(game::Configurations configurations, game::GameRules gameRules, game::Constants constants, game::GameState gameState);

    game::Configurationss getConfigurations();
    game::GameRules getRules();
    game::Constants getConstants();
    game::GameState getGameState();

private:
    
    game::Configurations configurations;

    game::GameRules gameRules;

    game::Constants constants;

    game::GameState gameState;
};
}