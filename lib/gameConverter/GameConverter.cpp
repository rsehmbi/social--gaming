#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;
using game::VariableType;

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
    for ( auto it: jsonConfigs["setup"].items() )
    {
        // Errors are not handled yet.
        // Also assuming the prompt as key, there are good chances prompt might refer to string prompt to ask user
        // Will Update as Requirements become more clear
        configurations.setup[it.key()]  = it.value();
        configurations.prompt = it.key();
    }
    google::FlushLogFiles(google::INFO);
    return configurations;
}

GameRules 
GameConverter::convertGameRules(const nlohmann::json& jsonRules){

    // TODO : create GameRules from json.
    
    game::GameRules gameRules;
    return gameRules;
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

        std::cout << std::get<int>(std::get<game::ListVariant>(stateVariables.getVariable(key))[0]) << std::endl;
    }

    
    
    // std::cout << std::get<int>(std::get<game::listVariant>(stateVariables.getVariable("winners"))[0]) << std::endl;
    std::cout << "\nEnd of convert" << std::endl;
    return stateVariables;
}