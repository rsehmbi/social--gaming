#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Rule;
using game::RuleContainer;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;
using game::RuleType;

Game
GameConverter::createGame(const nlohmann::json& jsonGame){

    LOG(INFO) << "creating game from json";
    game::Configurations configs = convertConfigurations(jsonGame["configurations"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants = convertConstants(jsonGame["constants"]);
    game::GameState gameState = convertState(jsonGame["variables"], jsonGame["per-player"], jsonGame["per-audience"]);

    game::Game createdGame {configs, gameRules, constants, gameState};
    
    return createdGame;
}

Configurations 
GameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    
    // TODO : create congurations from json.

    game::Configurations configurations;
    return configurations;
}

GameRules 
GameConverter::convertGameRules(const nlohmann::json& jsonRules){
    game::GameRules gameRules;
    
    // Loop through all the rules
    for(auto jsonRule: jsonRules) {
        auto ruleName = jsonRule["rule"];

        // Construct the rule container to hold rule information
        // by adding the the key value pairs of the rule
        RuleContainer ruleContainer = constructRuleContainer(jsonRule);
        Rule rule(game::matchRuleType(ruleName), ruleContainer);

        // Adds rule to game rules
        gameRules.addRule(rule);
    }

    return gameRules;
}

RuleContainer
GameConverter::constructRuleContainer(const nlohmann::json& jsonRule) {
    RuleContainer ruleContainer;
    
    // Iterates through all key value pairs in the json rule object
    // and adds them to the rule container
    for (auto& item : jsonRule.items()) {
        ruleContainer.add(item.key(), item.value());
    }

    return ruleContainer;
}

Constants 
GameConverter::convertConstants(const nlohmann::json& jsonConstants){

    // TODO : create Constants from json.
    
    game::Constants constants;
    return constants;
}

GameState 
GameConverter::convertState(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, const nlohmann::json& perAudience){
    
     // TODO : create GameState from json.

    game::GameState gameState;
    return gameState;
}