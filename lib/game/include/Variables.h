#pragma once

#include <vector>
#include <variant>
#include <string>
#include <Player.h>
#include <iostream>
#include <unordered_map>

namespace game {
    //From project spec: "Values may themselves be (1) maps from names to values, 
    //(2) lists of values, or (3) literal strings, numbers, or booleans."

    //rock paper scissor game has variable winners; which can be list of winning id's
    //vector is used because it is the representation inside JSON object
    //add additional data types into variant as needed
    using ListVariant = std::vector<std::variant<PlayerID, int> >;


    //add additional data types into variant as needed
    using VariableVariant = std::variant<ListVariant, std::string, int>;


    enum class VariableType {
        MapType,
        ListType,
        StringType,
        NumberType,
        BoolType
    };

    class Variables{
        public:
            VariableVariant getVariable(const std::string& variableName) const;
            VariableType getVariableType(const std::string &varName) const;
            
            template <class T>
            void insertVariable (const std::string& key, const T& val, VariableType valType) {
                varMap.emplace(key, val);
                varNameTypeMap.emplace(key, valType);
            }
            
            
        private:
            //map of string name given in JSON to a specific variable. Use variant to hold different types
            //*for now just implementing for the rock paper scissor game which only has list variable
            std::unordered_map<std::string, VariableVariant> varMap;

            //maps variable name to its type to help rule functions to determine which type it is operating on
            //eg: "winner" : ListType which means it is a std::vector<variant<...>>
            std::unordered_map<std::string, VariableType> varNameTypeMap;
    };
}