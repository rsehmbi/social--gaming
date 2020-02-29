#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Rule;
using game::RuleContainer;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;


Game
GameConverter::createGame(const nlohmann::json& jsonGame){

    LOG(INFO) << "Creating Game From Json" << jsonGame.dump();
    game::Configurations configs = convertConfigurations(jsonGame["configuration"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants = convertConstants(jsonGame["constants"]);
    game::GameState gameState = convertState(jsonGame["variables"], jsonGame["per-player"], jsonGame["per-audience"]);

    game::Game createdGame {configs, gameRules, constants, gameState};
    return createdGame;
}

Configurations 
GameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    game::Configurations configurations(jsonConfigs["name"],jsonConfigs["audience"],jsonConfigs["player count"]["min"],jsonConfigs["player count"]["max"]);
    for ( auto config: jsonConfigs["setup"].items() )
    {
        // Errors are not handled yet.
        // Also assuming the prompt as key, there are good chances prompt might refer to string prompt to ask user
        // Will Update as Requirements become more clear
        configurations.setup[config.key()]  = config.value();
        configurations.prompt = config.key();
        std::ostringstream outStr;
        outStr << "Connected to session: " << config.key() << "\n";
    }
    google::FlushLogFiles(google::INFO);
    return configurations;
}

GameRules 
GameConverter::convertGameRules(const nlohmann::json& jsonRules){
    game::GameRules gameRules;
    
    // Loop through all the rules
    for(auto jsonRule: jsonRules) {
        auto ruleName = jsonRule["rule"];

        // Constructs appropriate rule object
        // Example, if the rule name is "shuffle",
        // then it will construct a shuffle rule object
        // which is a subclass to the Rule class
        Rule rule = constructRuleObject(ruleName);

        // Construct the rule container for the above object
        // by adding the the key value pairs of the rule
        RuleContainer ruleContainer = constructRuleContainer(jsonRule);

        // Assigns the rule container to the rule object
       // rule.setRule(ruleContainer);

        // Adds rule to game rules
        gameRules.addRule(rule);
    }

    return gameRules;
}

Rule
GameConverter::constructRuleObject(const nlohmann::json& jsonRuleName) {
    // TO DO: Implement this using enums and switch statements
    // TO DO: Add in all the remaing rules
    // Rule returnObject;
    // if (jsonRuleName == "global-message") {
    //     game::GlobalMessageRule globalMessageRule;
    //     returnObject = globalMessageRule;
    // }

    // return returnObject;
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

