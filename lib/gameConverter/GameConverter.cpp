#include "GameConverter.h"


game::Game
gameConverter::GameConverter::createGame(const nlohmann::json& jsonGame){

    game::Configurations configs = convertConfigurations(jsonGame["configurations"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants = convertConstants(jsonGame["constants"]);
    game::GameState gameState = convertState(jsonGame["variables"], jsonGame["per_player"], jsonGame["per_audience"]);

    game::Game createdGame {configs, gameRules, constants, gameState};

    return createdGame;
}

game::Configurations 
gameConverter::GameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    
    // TODO : create congurations from json.

    game::Configurations configurations;
    return configurations;
}

game::GameRules 
gameConverter::GameConverter::convertGameRules(const nlohmann::json& jsonRules){

    // TODO : create GameRules from json.

    game::GameRules gameRules;
    return gameRules;
}

game::Constants 
gameConverter::GameConverter::convertConstants(const nlohmann::json& jsonConstants){

    // TODO : create Constants from json.
    
    game::Constants constants;
    return constants;
}

game::GameState 
gameConverter::GameConverter::convertState(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, const nlohmann::json& perAudience){
    
     // TODO : create GameState from json.

    game::GameState gameState;
    return gameState;
}