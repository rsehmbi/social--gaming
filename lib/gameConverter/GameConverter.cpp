#include "GameConverter.h"

using gameConverter::GameConverter;
using game::Game;
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
    google::FlushLogFiles(google::INFO);
    LOG(INFO) << configurations.getGameName();
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