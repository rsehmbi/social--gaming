#pragma once

#include "json.hpp"
#include "Game.h"
#include <glog/logging.h>

using game::Configurations;

namespace gameConverter{
    class GameConverter{

        public:
            GameConverter();

            // Creates a game object from jsonGame.
            game::Game createGame(const nlohmann::json& jsonGame);
    
        private:
            
            game::Configurations convertConfigurations(const nlohmann::json& jsonConfigs);
    
            game::Constants convertConstants(const nlohmann::json& jsonConstants);
    
            game::GameRules convertGameRules(const nlohmann::json& jsonRules);
            game::Rule constructRuleObject(const nlohmann::json& jsonRuleName);
            game::RuleContainer constructRuleContainer(const nlohmann::json& jsonRule);
            game::Rule constructRule(nlohmann::json jsonRule);
            game::Rule constructNestedRule(nlohmann::json jsonRule);
            game::Rule constructRuleWithCases(nlohmann::json jsonRule);
            void addJsonKeyValueToRuleContainer(game::RuleContainer& ruleContainer, nlohmann::json key, nlohmann::json value);
    
    
            game::GameState convertState(const nlohmann::json& gameVariables, 
                const nlohmann::json& perPlayer, const nlohmann::json& perAudience);
    
    
            game::Variables convertVariables(const nlohmann::json& gameVariables);

            friend class ConvertGameRulesTest;

    friend class ConvertGameRulesTest;
    };

}