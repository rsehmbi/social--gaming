#include <nlohmann/json.hpp>
#include "game.h"

namespace gameConverter{
class gameConverter{

public:

    // Creates a game object from jsonGame.
    game::game createGame(const nlohmann::json& jsonGame);

private:
    
    game::configurations convertConfigurations(const nlohmann::json& jsonConfigs);

    game::gameRules convertGameRules(const nlohmann::json& jsonRules);

    game::variables convertVariables(const nlohmann::json& jsonVariables);

    game::constants convertConstants(const nlohmann::json& jsonConstants);
};
}