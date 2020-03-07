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

        json getNextRuleBlock(json jsonBlock);
        bool hasNestedRules(json ruleBlock);
        
    
    public:

        void executeReverse(GameState &state, const Constants &constants, Configurations configurations, std::string listName);
        void executeShuffle(GameState &state, const Constants &constants, Configurations configurations, std::string listName);
        void executeSort(GameState &state, const Constants &constants, Configurations configurations, std::string listName);
        void executeDeal(GameState &state, const Constants &constants,
                Configurations configurations, int count, int from, int to);

        json getUpdate();
        void processRules(json gameRules, json gameData);
        void shuffleList(ListName& list);
        void sortList(ListName& list);
        void dealList(ListName From, ListName To, Count count);
    };
}

#endif