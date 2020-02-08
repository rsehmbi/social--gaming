#include "gameConverter.h"

game::game GameConverter::createGame(const nlohmann::json& jsonGame){

    game::Configurations configs = converConfigurations(jsonGame["configurations"]);
    game::GameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::Constants constants = convertConstants(jsonGame["constants"]);
    game::Variables variables = convertConfigurations(jsonGame["variables"], jsonGame["per_player"], jsonGame["per_audience"]);

    game::Game createdGame {configs, gameRules, constants, variables};
    return createdGame;
}

game::Configurations GameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    
}

game::GameRules GameConverter::convertGameRules(const nlohmann::json& jsonRules){

}

game::Constants GameConverter::convertConstants(const nlohmann::json& jsonConstants){

}

game::Variables GameConverter::convertVariables(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, const nlohmann::json& perAudience){

}