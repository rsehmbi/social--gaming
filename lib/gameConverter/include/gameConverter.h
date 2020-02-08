#include <nlohmann/json.hpp>
#include "game.h"

namespace gameConverter{
class GameConverter{

public:

    // Creates a game object from jsonGame.
    game::Game createGame(const nlohmann::json& jsonGame);

private:
    
    game::Configurations convertConfigurations(const nlohmann::json& jsonConfigs);

    game::GameRules convertGameRules(const nlohmann::json& jsonRules);

    game::Variables convertVariables(const nlohmann::json& jsonVariables);

    game::Constants convertConstants(const nlohmann::json& jsonConstants);
};
}