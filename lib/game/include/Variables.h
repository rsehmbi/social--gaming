#pragma once

#include <vector>
#include <variant>
#include <string>
#include <list>
#include <player.h>
#include <iostream>
#include <unordered_map>

namespace game {
    //From project spec: "Values may themselves be (1) maps from names to values, 
    //(2) lists of values, or (3) literal strings, numbers, or booleans."

    //rock paper scissor game has variable winners; which can be list of winning id's
    //add additional data types into variant as needed
    using listVariant = std::list<std::variant<PlayerID> >;


    //add additional data types into variant as needed
    using VariableVariant = std::variant<listVariant, std::string>;

    class Variables{
        public:
            VariableVariant getVariable(const std::string& variableName) const;
            
            template <class T>
            void insertVariable (const std::string& key, const T& val) {
                varMap.emplace(key, val);
            }
            
            
        private:
            //map of string name given in JSON to a specific variable. Use variant to hold different types
            //*for now just implementing for the rock paper scissor game which only has list variable
            std::unordered_map<std::string, VariableVariant> varMap;
    };
}