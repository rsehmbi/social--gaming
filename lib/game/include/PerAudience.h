#pragma once

#include <Variables.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_map>
#include <utility>

namespace game {
    enum class AudienceID{
        std::string,
        int
    }
    
    class PerAudience{
        public:
            PerAudience(const std::unordered_map<std::string, Variable>& varMap); 
            
            void addNewAudience(const AudienceID& id);
            
            //TODO: add setter for specific audience
        private:
            template <class T>
            void insertVariable (const std::string& key, const T& val, VariableType valType); // needs to eachAudienceMap if insert after data initialized
            
            std::unordered_map<std::string, Variable> varMap; //holds all variables for an audience
            std::unordered_map<AudienceID, std::unordered_map<std::string, Variable>> eachAudienceMap; //holds a list of unique AudienceID, each audience holds a varMap
    };
}
