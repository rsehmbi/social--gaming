#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "../../jsonReader/include/dsl.h"
#include "json.hpp"
#include "Game.h"

using game::GameState;
using game::Constants;
using game::Configurations;
using game::Rule;
using game::Variables;
using game::VariableVariant;

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

        void executeReverse(GameState &state, const Constants &constants, Configurations configurations, ListName listName);
        void executeShuffle(GameState &state, const Constants &constants, Configurations configurations, ListName listName);
        void executeSort(GameState &state, const Constants &constants, Configurations configurations, ListName listName);
        void executeDeal(GameState &state, const Constants &constants,
                Configurations configurations, Count count, From from, To to);

        json getUpdate();
        void processRules(json gameRules, json gameData);
    };
}

#endif