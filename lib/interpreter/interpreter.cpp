#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <chrono>
#include <glog/logging.h>

using interpreter::Interpreter;
using namespace game;
using namespace std;

Interpreter::Interpreter () {
}

void 
Interpreter::setCurrentGameSession(const GameSessionInterface* session, CurrentGameState* _gameState, 
    const Constants* _constants, const GameRules* _rules){
    mSession = session;
    gameState = _gameState;
    constants = _constants;
    rules = _rules;
}

void Interpreter::processRules(json gameRules, json gameData){
    json ruleBlock = getNextRuleBlock(gameRules);
    if(hasNestedRules(ruleBlock)){
        processRules(ruleBlock, gameData);
    }
    //calls processor to process rule block
}

std::shared_ptr<Variable> processToList(std::string domainLanguage){
    //TODO: implement the evaluation of command such as
    // !players.elements.weapon.contains(weapon.name) To a vector.
    // DomainNameTranslator's job?
    std::shared_ptr<Variable> listVariablePtr = std::make_shared<Variable>();
    listVariablePtr->varType = VariableType::ListType;

    return listVariablePtr;
}
/*
void executeExtend(GameState& state, Rule& rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string targetList = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> targetListPtr = state.variables.getVariable(targetList);
    //must be a list type
    if(targetListPtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeExtend error, type mismatch; not ListType" <<std::endl;
    }
    std::string listCommands = std::get<std::string>(container.ruleInformation.at(RuleField::list));
    std::shared_ptr<Variable> sourceVariablePtr = processToList(listCommands);

    targetListPtr->listVar.insert(targetListPtr->listVar.end(),
                    sourceVariablePtr->listVar.begin(), sourceVariablePtr->listVar.end());
}

void executeReverse(GameState& state, Rule& rule){
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> listVariablePtr = state.variables.getVariable(listName);
    //must be a list type
    if(listVariablePtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeReverse error, type mismatch; not ListType" <<std::endl;
    }
    std::reverse(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end());
}
*/
void Interpreter::executeInputChoice(const Constants &constants, GameSessionInterface* session, 
                                    UserVariables& to, Input& prompt, list<std::string>& choices, 
                                    Input& result, Count& timeout){
    if (session->getWaitingInputFlag==false){
        try {
            int connectionID = to.getUserVariables.getVariables("id");
            session->msgUser(connectionID, prompt);
            for (auto itemInList : choices){
                session->msgUser(connectionID, itemInList);
            }
            return;
            //Work in Progress; need to retrieve input from user

        }
        catch (exception &e){
            LOG(INFO) << "Unable to send msg to player" << e.what();
        }
    }
    else{
        //TimeoutRoute
        //Need to figure out how to process Timeout
        auto globalTimer = std::chrono::system_clock::now(); //placeholder for GlobabTimer
        auto currentTime = std::chrono::system_clock::now();
        if (chrono::duration_cast<chrono::seconds>(currentTime-globalTimer).count()< timeout){
            return; //not enough time has elapsed yet
        }
        else{
            std::string input = session->retrieveMsg;
            //to.getUserVariables.insert() TODO: function to insert variable
            session->getWaitingInputFlag=true;
            
        }
    }
}