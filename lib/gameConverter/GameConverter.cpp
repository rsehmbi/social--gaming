#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Rule;
using game::RuleContainer;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;
using game::Variables;
using game::Variable;
using game::VariableType;
using game::RuleType;

GameConverter::GameConverter() {}

Game
GameConverter::createGame(const nlohmann::json& jsonGame){
    LOG(INFO) << "Creating Game From Json" << jsonGame.dump();
    game::Configurations configs = convertConfigurations(jsonGame["configuration"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants;
    game::GameState gameState = convertState(jsonGame["variables"], jsonGame["per-player"], jsonGame["per-audience"], jsonGame["constants"]);

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
        else if(game::hasCasesInRule(jsonRule)) {
            rule = constructRuleWithCases(jsonRule);
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

Rule
GameConverter::constructRuleWithCases(nlohmann::json jsonRule) {
    RuleContainer ruleContainer;
    std::vector<Rule::Case> cases;

    auto& ruleName = jsonRule["rule"];
    auto& jsonCases = jsonRule["cases"];
    
    for(auto& caseItem: jsonCases.items()) {
        Rule::Case caseContainer;
        
        if(caseItem.value()["condition"].type() == nlohmann::json::value_t::boolean) {
            caseContainer.condition = caseItem.value()["condition"].get<bool>();
        } else {
            caseContainer.condition = caseItem.value()["condition"].get<std::string>();
        }
        
        // convertGameRules returns a GameRules object
        caseContainer.rules = convertGameRules(caseItem.value()["rules"]).getRules();
        cases.push_back(caseContainer);
    }
    
    jsonRule.erase("cases");
    for (auto& item : jsonRule.items()) {
        addJsonKeyValueToRuleContainer(ruleContainer, item.key(), item.value());
    }

    Rule rule(game::matchRuleType(ruleName), ruleContainer, cases);
    return rule;
}

void GameConverter::addJsonKeyValueToRuleContainer(RuleContainer& ruleContainer, nlohmann::json jsonKey, nlohmann::json value) {
    game::RuleField key = game::stringToRuleField[jsonKey];

    switch(value.type()) {
        case nlohmann::json::value_t::string:
            ruleContainer.add(key, value.get<std::string>());
            break;
        case nlohmann::json::value_t::number_unsigned:
            ruleContainer.add(key, value.get<int>());
            break;
        case nlohmann::json::value_t::boolean:
            ruleContainer.add(key, value.get<bool>());
            break;
        default:
            // If value is not of type string, int, or bool, then produce an error
            //assert("Error: Invalid value type" == 0);
            break;
    }

    return;
}

Constants 
GameConverter::convertConstants(const nlohmann::json& jsonConstants){

    // TODO : create Constants from json.
    
    game::Constants constants;
    return constants;
}

//typecheck helper function
VariableType determineValueTypeJSON(const nlohmann::json& value){
    if(value.is_number()){return VariableType::NumberType;}
    if(value.is_array()){return VariableType::ListType;}
    if(value.is_boolean()){return VariableType::BoolType;}
    if(value.is_string()){return VariableType::StringType;}
    if(value.is_object()){return VariableType::MapType;}
    LOG(INFO) << "Unsupported ValueType, need to implement";
    return VariableType::NumberType;
}

//process JSON recursively
void convertVariableHelperJSON(std::shared_ptr<Variable> variablePtr, const nlohmann::json& value){
    VariableType valType = determineValueTypeJSON(value);
    variablePtr->varType = valType;
    switch(valType) {
        case VariableType::NumberType: 
        {
            variablePtr->intVar = value.get<int>();
            break;
        }
        case VariableType::StringType: 
        {
            variablePtr->stringVar = value.get<std::string>();
            break;
        }
        case VariableType::BoolType: 
        {
            variablePtr->boolVar = value.get<bool>();
            break;
        }             
        case VariableType::ListType:
        {
            //recursively call convertVariableHelperJSON to process each element in list
            for(auto& element : value){
                std::shared_ptr<Variable> elementPtr = std::make_shared<Variable>();
                convertVariableHelperJSON(elementPtr, element);
                variablePtr->listVar.push_back(elementPtr);
            }
            break;
        }
        case VariableType::MapType:
        {
            //recursively call convertVariableHelperJSON to process each pair in map
            for(auto& [key, val]: value.items()){
                std::shared_ptr<Variable> valPtr = std::make_shared<Variable>();
                convertVariableHelperJSON(valPtr, val);
                variablePtr->mapVar[key] = valPtr;
            }
            break;
        }
        default:
            LOG(ERROR) << "unsupported valType, please implement";
    }
}

GameState 
GameConverter::convertState(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, 
    const nlohmann::json& perAudience,
    const nlohmann::json& constants){
    
    // create variable objects for all the starting variables and 
    // strore them in the gameState class object. When playing game
    // game start with a copy of these (each player or user will have
    // his own copy).
    auto gameVariablesPtr = std::make_shared<Variable>();
    auto playerVariablesPtr = std::make_shared<Variable>();
    auto audienceVariablesPtr = std::make_shared<Variable>();
    auto constantsPtr = std::make_shared<Variable>();

    convertVariableHelperJSON(gameVariablesPtr, gameVariables);
    convertVariableHelperJSON(playerVariablesPtr, perPlayer);
    convertVariableHelperJSON(audienceVariablesPtr, perAudience);
    convertVariableHelperJSON(constantsPtr, constants);
    

    return GameState {
        std::move(gameVariablesPtr),
        std::move(playerVariablesPtr),
        std::move(audienceVariablesPtr),
        std::move(constantsPtr)
    };
}

Variables GameConverter::convertVariables(const nlohmann::json& gameVariables){
    // Variable conversion and creation
    LOG(INFO) << "\nStart of convert variable" << std::endl;

    Variables stateVariables;

    for (auto& [key, value] : gameVariables.items()){
        std::shared_ptr<Variable> varPtr = std::make_shared<Variable>();
        stateVariables.createVariable(key, varPtr);
        convertVariableHelperJSON(varPtr, value);
    }

    LOG(INFO) << "\nEnd of convert variable" << std::endl;
    return stateVariables;
}
