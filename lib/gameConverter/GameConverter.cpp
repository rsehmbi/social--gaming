#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
using game::Configurations;
using game::Constants;
using game::GameState;
using game::GameRules;

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

    game::GameState gameState;
    return gameState;
}