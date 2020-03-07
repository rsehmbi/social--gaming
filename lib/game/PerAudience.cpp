#include "include/PerAudience.h"

using game::PerAudience;
using game::AudienceID;
using game::Variable;

PerAudience:PerAudience(const std::unordered_map<std::string, Variable>& variableMap):
    varMap(variableMap){};

void PerAudience::insertVariable(const std::string& key, const T& val, VariableType valType){
    Variable variable{val, valType};
    this->varMap.emplace(key, variable);
}

void PerAudience::addNewAudience(const AudienceID& id){
    this->eachAudienceMap.emplace(id, this->varMap);
}