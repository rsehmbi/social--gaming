#include "json.hpp"
#include "Game.h"

#include <glog/logging.h>

namespace gameConverter{
class GameConverter{

public:

    // Creates a game object from jsonGame.
    game::Game createGame(const nlohmann::json& jsonGame);

private:
    
    game::Configurations convertConfigurations(const nlohmann::json& jsonConfigs);

    game::GameRules convertGameRules(const nlohmann::json& jsonRules);
    game::Rule constructRuleObject(const nlohmann::json& jsonRuleName);
    game::RuleContainer constructRuleContainer(const nlohmann::json& jsonRule);

    game::Constants convertConstants(const nlohmann::json& jsonConstants);

    game::GameState convertState(const nlohmann::json& gameVariables, 
        const nlohmann::json& perPlayer, const nlohmann::json& perAudience);

    friend class gameConverterTester;

};
}