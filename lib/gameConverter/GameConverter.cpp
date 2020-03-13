#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Rule;
using game::RuleContainer;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;

using game::VariableType;
using game::RuleType;

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
    LOG(INFO) << "Creating Configurations from Json";
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
    LOG(INFO) << "Creating game rules from Json";
    game::GameRules gameRules;

    // Loop through all the rules
    for(auto& jsonRule: jsonRules) {
        Rule rule;
        if(game::isNestedJsonRule(jsonRule)) {
            rule = constructNestedRule(jsonRule);
        }
        else {
            rule = constructRule(jsonRule);
        }
    
        // Adds rule to game rules
        gameRules.addRule(rule);
    }

    return gameRules;
}

Rule
GameConverter::constructRule(nlohmann::json jsonRule) {
    RuleContainer ruleContainer;

    // Iterates through all key value pairs in the json rule object
    // and adds them to the rule container
    for (auto& item : jsonRule.items()) {
        addJsonKeyValueToRuleContainer(ruleContainer, item.key(), item.value());
    }

    auto& ruleName = jsonRule["rule"];
    Rule rule(game::matchRuleType(ruleName), ruleContainer);
    return rule;
}

Rule
GameConverter::constructNestedRule(nlohmann::json jsonRule) {
    RuleContainer ruleContainer;
    std::vector<Rule> nestedRules;

    // GameRules is just a wrapper for a vector of rules so we can call convertGameRules
    // to convert the array of nested rules and then extract the vector
    auto& nestedJsonRules = jsonRule["rules"];
    GameRules rules =  GameConverter::convertGameRules(nestedJsonRules);
    nestedRules = rules.getRules();

    // Iterates through all key value pairs in the json rule object
    // except for nested rules and adds them to the rule container.
    jsonRule.erase("rules");
    for (auto& item : jsonRule.items()) {
        addJsonKeyValueToRuleContainer(ruleContainer, item.key(), item.value());
    }

    auto& ruleName = jsonRule["rule"];
    Rule rule(game::matchRuleType(ruleName), ruleContainer, nestedRules);
    return rule;
}

void GameConverter::addJsonKeyValueToRuleContainer(RuleContainer& ruleContainer, nlohmann::json key, nlohmann::json value) {
    std::string keyStr = key.get<std::string>();

    switch(value.type()) {
        case nlohmann::json::value_t::string:
            ruleContainer.add(keyStr, value.get<std::string>());
            break;
        case nlohmann::json::value_t::number_integer:
            ruleContainer.add(keyStr, value.get<int>());
            break;
        case nlohmann::json::value_t::boolean:
            ruleContainer.add(keyStr, value.get<bool>());
            break;
        default:
            // If value is not of type string, int, or bool, then produce an error
            assert("Error: Invalid value type" == 0);
            break;
    }

    return;
}

// TO DO: Remove since it is no longer used
RuleContainer
GameConverter::constructRuleContainer(const nlohmann::json& jsonRule) { 
    RuleContainer ruleContainer;

    // Iterates through all key value pairs in the json rule object
    // and adds them to the rule container
    for (auto& item : jsonRule.items()) {
        if (item.key() == "rules") {
            // Do nothing
        } 
        else {
            addJsonKeyValueToRuleContainer(ruleContainer, item.key(), item.value());
        }
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

    game::Variables stateVariable = convertVariables(gameVariables);
    
    game::GameState gameState;
    return gameState;
}


game::VariableType determineValueType(const nlohmann::json& value){
    using game::VariableType;
    if(value.is_number()){return VariableType::NumberType;}
    if(value.is_array()){return VariableType::ListType;}
    if(value.is_boolean()){return VariableType::BoolType;}
    if(value.is_string()){return VariableType::StringType;}
    if(value.is_object()){return VariableType::MapType;}
    LOG(INFO) << "Unsupported ValueType, need to implement";
}

game::Variables GameConverter::convertVariables(const nlohmann::json& gameVariables){
    using game::VariableType;
    // Variable conversion and creation
    //vector, map, bool, int, string

    //check type

    std::cout << "Convert Variable:" << std::endl;


    game::Variables stateVariables;

    for (auto& [key, value] : gameVariables.items()){
        VariableType valType = determineValueType(value);
        
        switch(valType) {
            case VariableType::NumberType: 
                stateVariables.insertVariable(key, value.get<int>(), valType);
                break;
            case VariableType::ListType:
                stateVariables.insertVariable(key, game::ListVariant{1}, valType);
                break;
            default:
                LOG(INFO) << "unsupported valType";
        }

        // std::cout << std::get<int>(std::get<game::ListVariant>(stateVariables.getVariable(key))[0]) << std::endl; ////****
    }

    
    
    // std::cout << std::get<int>(std::get<game::listVariant>(stateVariables.getVariable("winners"))[0]) << std::endl; ////****
    std::cout << "\nEnd of convert" << std::endl;
    return stateVariables;
}
