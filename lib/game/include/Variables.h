#pragma once

#include <vector>
#include <variant>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>

namespace game {
    using PlayerID = std::variant<int, std::string>;

    enum class VariableType {
        MapType,
        ListType,
        StringType,
        NumberType,
        BoolType
    };
    //From project spec: "Values may themselves be (1) maps from names to values, 
    //(2) lists of values, or (3) literal strings, numbers, or booleans."

    //rock paper scissor game has variable winners; which can be list of winning id's
    //vector is used because it is the representation inside JSON object
    //add additional data types into variant as needed
    using ListVariant = std::vector<std::variant<PlayerID, int> >;


    //add additional data types into variant as needed
    using VariableVariant = std::variant<ListVariant, std::string, int>; 

    using VariablePair = std::pair<VariableVariant, VariableType>; // contains the variable value + that variable type, can be named better

    class Variables{
        public:
            VariablePair getVariable(const std::string& variableName) const;
            VariableType getVariableType(const std::string &varName) const;
            
            template <class T>
            void insertVariable (const std::string& key, const T& val, VariableType valType) {
                VariablePair variable{val, valType};
                varMap.emplace(key, variable);
            }
            
            
        private:
            //map of string name given in JSON to a specific variable. Use variant to hold different types
            //*for now just implementing for the rock paper scissor game which only has list variable
            std::unordered_map<std::string, VariablePair> varMap;
    };
}
