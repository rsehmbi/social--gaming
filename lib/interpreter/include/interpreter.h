#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "../../jsonReader/include/dsl.h"
#include "json.hpp"
#include "Game.h"
#include <glog/logging.h>
#include "GameSessionInterface.h"

using game::ListName;////****
using game::Mode;
using game::VariableName;
using game::Count;
using game::TimerLength;
using game::Input;////****

using game::GameState;
using game::Constants;
using game::Configurations;
using game::GameRules;
using game::Rule;
using game::Variables;
using game::Variable;
using game::VariableType;

using nlohmann::json;
//responsible for checking rule inside json 

namespace interpreter{

    class Interpreter{
    private:

        const GameSessionInterface* mSession;

        RunningGameState* gameState;

        const GameRules* rules;


        json gameRules;
        json gameData;  

        json getNextRuleBlock(json jsonBlock);
        bool hasNestedRules(json ruleBlock);
        
    
    public:

        Interpreter();

        void setCurrentGameSession(const GameSessionInterface* session, RunningGameState* gameState, const GameRules* rules);
        void executeShuffle(Rule& rule);
        void executeSort(Rule& rule);
        void executeDeal(Rule& rule);

        void executeAdd(GameState &state, VariableName& toVariable, VariableName& value);
        void executeTimer(GameState &state, VariableName& value);
        void processRules(json gameRules, json gameData);
        void executeReverse(GameState &state, Rule& rule);
        void executeExtend(GameState &state, Rule& rule);
        
    };
}

#endif