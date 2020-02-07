#include "gameConverter.h"

game::game gameConverter::createGame(const nlohmann::json& jsonGame){

    game::configurations configs = converConfigurations(jsonGame["configurations"]);
    game::gameRules gameRules = convertGameRules(jsonGame["rules"]);
    game::constants constants = convertConstants(jsonGame["constants"]);
    game::variables variables = convertConfigurations(jsonGame["variables"], jsonGame["per_player"], jsonGame["per_audience"]);

    game::game createdGame {configs, gameRules, constants, variables};
    return createdGame;
}

game::configurations gameConverter::convertConfigurations(const nlohmann::json& jsonConfigs){
    
}

game::gameRules gameConverter::convertGameRules(const nlohmann::json& jsonRules){

}

game::constants gameConverter::convertConstants(const nlohmann::json& jsonConstants){

}

game::variables gameConverter::convertVariables(const nlohmann::json& gameVariables, 
    const nlohmann::json& perPlayer, const nlohmann::json& perAudience){

}