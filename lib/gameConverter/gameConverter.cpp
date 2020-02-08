#include "gameConverter.h"

game::Game 
gameConverter::GameConverter::createGame(const nlohmann::json& jsonGame){

    game::Configurations configs = convertConfigurations(jsonGame["configurations"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants = convertConstants(jsonGame["constants"]);
    game::GameState gameState = convertConfigurations(jsonGame["variables"], jsonGame["per_player"], jsonGame["per_audience"]);

    game::Game createdGame {configs, gameRules, constants, gameState};
    return createdGame;
}

game::Configurations 
gameConverter::GameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    
}

game::GameRules 
gameConverter::GameConverter::convertGameRules(const nlohmann::json& jsonRules){

}

game::Constants 
gameConverter::GameConverter::convertConstants(const nlohmann::json& jsonConstants){

}

game::gameState 
gameConverter::GameConverter::convertState(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, const nlohmann::json& perAudience){

}