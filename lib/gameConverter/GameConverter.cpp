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

GameConverter::GameConverter(){
    ruleFieldMap["rule"] = game::RuleFields::rule;
    ruleFieldMap["list"] = game::RuleFields::list;
    ruleFieldMap["element"] = game::RuleFields::element;
    ruleFieldMap["rules"] = game::RuleFields::rules;
    ruleFieldMap["until"] = game::RuleFields::until;
    ruleFieldMap["cases"] = game::RuleFields::cases;
    ruleFieldMap["target"] = game::RuleFields::target;
    ruleFieldMap["from"] = game::RuleFields::from;
    ruleFieldMap["to"] = game::RuleFields::to;
    ruleFieldMap["count"] = game::RuleFields::count;
    ruleFieldMap["roles"] = game::RuleFields::roles;
    ruleFieldMap["value"] = game::RuleFields::value;
    ruleFieldMap["duration"] = game::RuleFields::duration;
    ruleFieldMap["mode"] = game::RuleFields::mode;
    ruleFieldMap["flag"] = game::RuleFields::flag;
    ruleFieldMap["prompt"] = game::RuleFields::prompt;
    ruleFieldMap["result"] = game::RuleFields::result;
    ruleFieldMap["score"] = game::RuleFields::score;
    ruleFieldMap["ascending"] = game::RuleFields::ascending;
        
}

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
    for(auto& jsonRule: jsonRules) { ////**** removed .items()
        auto& ruleName = jsonRule["rule"];

        // Construct the rule container to hold rule information
        // by adding the the key value pairs of the rule
        RuleContainer initialContainer;
        RuleContainer ruleContainer = constructRuleContainer(jsonRule, initialContainer);
        Rule rule(game::matchRuleType(ruleName), ruleContainer);

        // Adds rule to game rules
        gameRules.addRule(rule);
    }

    return gameRules;
}

RuleContainer
GameConverter::constructRuleContainer(const nlohmann::json& jsonRule, RuleContainer& ruleContainer) {    
    // Iterates through all key value pairs in the json rule object
    // and adds them to the rule container
    for (auto& item : jsonRule.items()) {
        if (item.value().size() == 1) {
            ruleContainer.add(ruleFieldMap[item.key()], item.value());
        } else {
            // If value contains nested JSON objects, use recursion to construct rule container.
            constructRuleContainer(item.value(), ruleContainer);
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

Variables GameConverter::convertVariables(const nlohmann::json& gameVariables){
    // Variable conversion and creation
    std::cout << "\nStart of convert variable" << std::endl;

    Variables stateVariables;

    for (auto& [key, value] : gameVariables.items()){
        std::shared_ptr<Variable> varPtr = std::make_shared<Variable>();
        stateVariables.createVariable(key, varPtr);
        convertVariableHelperJSON(varPtr, value);
    }

    std::cout << "\nEnd of convert variable" << std::endl;
    return stateVariables;
}
