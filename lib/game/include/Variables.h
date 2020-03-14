#pragma once

#include <vector>
#include <string>
#include <Player.h>
#include <iostream>
#include <unordered_map>
#include <memory>

namespace game {
    //From project spec: "Values may themselves be (1) maps from names to values, 
    //(2) lists of values, or (3) literal strings, numbers, or booleans."

    enum class VariableType {
        NoType,
        MapType,
        ListType,
        StringType,
        NumberType,
        BoolType
    };

    struct Variable {
        //default to NoType to indicate Variable is not initialized; ie the containing structure is empty
        VariableType varType = VariableType::NoType;
        int intVar;
        bool boolVar;
        std::string stringVar;
        std::unordered_map<std::string, std::shared_ptr<Variable>> mapVar;
        std::vector<std::shared_ptr<Variable>> listVar;
    };

    class Variables {
        public:
            //return ptr to variable held and allows modification directly
            std::shared_ptr<Variable> getVariable(const std::string& variableName) const;
            
            //take shared_ptr by value to create copy and move copy into variables map
            void createVariable (const std::string& key, std::shared_ptr<Variable> val);
                        
        private:
            //map of string name given in JSON to a specific variable
            std::unordered_map<std::string, std::shared_ptr<Variable>> variables;

    };
}
