#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "../../jsonReader/include/dsl.h"
#include "json.hpp"
#include "Game.h"
#include <glog/logging.h>
#include "GameSessionInterface.h"
// #include "DomainNameTranslator.h"


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
// using domainnametranslator::DomainNameTranslator;

using nlohmann::json;
//responsible for checking rule inside json 

namespace interpreter{

    class Interpreter{
    private:

        GameSessionInterface* mSession;
        RunningGameState* gameState;
        const Constants* constants;
        const GameRules* rules;

        json gameRules;
        json gameData;  

        json getNextRuleBlock(json jsonBlock);
        bool hasNestedRules(json ruleBlock);

        
    public:

        Interpreter();
        void setCurrentGameSession(GameSessionInterface* session, RunningGameState* gameState, 
                const Constants* constants, const GameRules* rules);
        
        void processRuleChoice(Rule &rule);

        // Control Structures
        void executeForEach(Rule &rule);
        void executeLoop(Rule &rule);
        void executeInparallel(Rule  &rule);
        void executeParallelFor(Rule &rule);
        void executeSwitch(Rule &rule);
        void executeWhen(Rule &rule);

        //List Operations
        void executeExtend(Rule& rule);
        void executeReverse(Rule& rule);

        void executeShuffle(Rule& rule);
        void executeSort(Rule& rule);
        void executeDeal(Rule& rule);
        void executeDiscard(Rule &rule);

        void executeAdd(Rule &rule);
        void executeTimer(Rule &rule);
        void processRules(Rule &rule);

        //Human Input Rules
        void executeInputChoice(Rule &rule);
        void executeInputText(Rule &rule);
        void executeInputVote(Rule &rule);

        //Output
        void executeMessage(Rule &rule);
        void executeGlobalMessage(Rule &rule);
        void executeScores(Rule &rule);
    };
}

#endif