#include "include/PerPlayer.h"

using game::PerPlayer;
using game::PlayerID;
using game::Variable;

PerPlayer::PerPlayer(const std::unordered_map<std::string, Variable>& variableMap):
    varMap(variableMap){};

void PerPlayer::insertVariable(const std::string& key, const T& val, VariableType valType){
    Variable variable{val, valType};
    this->varMap.emplace(key, variable);
}

void PerPlayer::addNewPlayer(const PlayerID& id){
    this->eachPlayerMap.emplace(id, this->varMap);
}