#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "../../jsonReader/include/dsl.h"
#include "json.hpp"
#include "Game.h"
#include "GameSession.h"

using game::ListName;////****
using game::Mode;
using game::VariableName;
using game::Count;
using game::TimerLength;
using game::Input;////****

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

        void executeReverse(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName);
        void executeShuffle(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName);
        void executeSort(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName);
        void executeDeal(GameState &state, const Constants &constants,
                Configurations &configurations, Count count, ListName &from, ListName &to);
        void executeDiscard(GameState &state, const Constants &constants,
                Configurations &configurations, Count count, ListName &from);
        void executeListAttributes(GameState &state, const Constants &constants,
                Configurations &configurations, ListName &list, ListType &type);

        void executeAdd(GameState &state, VariableName& toVariable, VariableName& value);
        void executeTimer(GameState &state, VariableName& value);
        void executeInputChoice(const Constants &constants, GameSession& session, Input& to, Input& prompt, Input& choices, Input& result, Count& timeout);

        //void executeInputChoice ()
    };
}

#endif