#pragma once

#include <Variables.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_map>
#include <utility>

namespace game {
    enum class PlayerID{
        std::string,
        int
    }
    
    class PerPlayer{
        public:
            PerPlayer(const std::unordered_map<std::string, Variable>& varMap); 
            
            void addNewPlayer(const PlayerID& id);

            //TODO: add setter for specific player
        private:
            template <class T>
            void insertVariable (const std::string& key, const T& val, VariableType valType); // needs to update eachPlayerMap if inserted after data initialized
            
            std::unordered_map<std::string, Variable> varMap; //holds all variables for a player
            std::unordered_map<PlayerID, std::unordered_map<std::string, Variable>> eachPlayerMap; //holds a list of unique PlayerID, each player holds a varMap
    };
}
