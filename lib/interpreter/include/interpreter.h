#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "include/dsl.h"
#include "json.hpp"

using nlohmann::json;
//responsible for checking rule inside json 

namespace interpreter{

    class Interpreter{
    private:
        json gameRules;
        json gameData;  
        std::unique_ptr<DSL> processor;

        json getNextRuleBlock(json jsonBlock);
        bool hasNestedRules(json ruleBlock);
        
    
    public:
        Interpreter(json rules, json data);
        ~Interpreter();

        json getUpdate();
        void processRules(json gameRules, json gameData);
    };
}

#endif