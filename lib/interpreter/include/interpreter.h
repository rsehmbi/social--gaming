#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "json.hpp"
#include "include/dsl.h"

//responsible for checking rule inside json 

namespace interpreter{

    class Interpreter{
    private:
        json gameRules;
        json gameData;  
        std::unique_ptr<DSL::DSL> processor(new processor());

        json getNextRuleBlock(json jsonBlock);
        boolean hasNestedRules(json ruleBlock);
        
    
    public:
        Interpreter(json rules, json data);
        ~Interpreter();

        json getUpdate();
        void processRules(json gameRules, json gameData);
    };
}

#endif