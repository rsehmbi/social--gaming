#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <random>       // std::default_random_engine
#include <chrono>

using interpreter::Interpreter;
using namespace game;
using namespace std;

Interpreter::Interpreter () {
}

void 
Interpreter::setCurrentGameSession(const GameSessionInterface* session, RunningGameState* gameState,
                                   const Constants* constants, const GameRules* rules){
    mSession = session;
    gameState = gameState;
    rules = rules;
    constants = constants;
}

//void interpreter::Interpreter::processRules(json gameRules, json gameData){
//    json ruleBlock = getNextRuleBlock(gameRules);
//    if(hasNestedRules(ruleBlock)){
//        processRules(ruleBlock, gameData);
//    }
//    //calls processor to process rule block
//}

std::shared_ptr<Variable> processToList(std::string domainLanguage){
    //TODO: implement the evaluation of command such as
    // !players.elements.weapon.contains(weapon.name) To a vector.
    // DomainNameTranslator's job?
    std::shared_ptr<Variable> listVariablePtr = std::make_shared<Variable>();
    listVariablePtr->varType = VariableType::ListType;

    return listVariablePtr;
}

void interpreter::Interpreter::executeExtend(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string targetList = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> targetListPtr =this->gameState->variables->getVariable(targetList);
    //must be a list type
    if(targetListPtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeExtend error, type mismatch; not ListType" <<std::endl;
    }
    std::string listCommands = std::get<std::string>(container.ruleInformation.at(RuleField::list));
    std::shared_ptr<Variable> sourceVariablePtr = processToList(listCommands);

    targetListPtr->listVar.insert(targetListPtr->listVar.end(),
                    sourceVariablePtr->listVar.begin(), sourceVariablePtr->listVar.end());
}

void interpreter::Interpreter::executeReverse(Rule &rule){
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    //must be a list type
    if(listVariablePtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeReverse error, type mismatch; not ListType" <<std::endl;
    }
    std::reverse(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end());
}

void interpreter::Interpreter::executeShuffle(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));

    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    try {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end(),std::default_random_engine(seed));
    }
    catch (exception &e)
    {
        LOG(INFO) << "Shuffle failed in Interpreter" << e.what();
    }
}

void interpreter::Interpreter::executeSort(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));

    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    try {
        std::sort(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end());
    }
    catch (exception &e)
    {
        LOG(INFO) << "Sort failed in Interpreter" << e.what();
    }
}

void interpreter::Interpreter::executeDeal(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string From = std::get<std::string>(container.ruleInformation.at(RuleField::from));
    std::string To = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    int Count =  std::get<int >(container.ruleInformation.at(RuleField::count));
    int numberOfElements = 0;
    std::shared_ptr<Variable> fromVariablePtr = processToList(From);
    std::shared_ptr<Variable> toVariablePtr = processToList(To);

    try {
        for (int iterator = 0; iterator < numberOfElements;iterator++ )
        {
            toVariablePtr->listVar.push_back(fromVariablePtr->listVar.front());
            fromVariablePtr->listVar.erase(fromVariablePtr->listVar.begin());
        }
    }
    catch (exception &e)
    {
        LOG(INFO) << "Deal failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeForEach(Rule &rule) {

}

void interpreter::Interpreter::executeLoop(Rule &rule) {

}

void interpreter::Interpreter::executeInparallel(Rule &rule) {

}

void interpreter::Interpreter::executeParallelFor(Rule &rule) {

}

void interpreter::Interpreter::executeSwitch(Rule &rule) {

}

void interpreter::Interpreter::executeWhen(Rule &rule) {

}

void interpreter::Interpreter::executeDiscard(Rule &rule) { 
    //Count will not work as intended if count datatype is not Int, such as winner.size, because DomainNameTranslator doesn't have the function to parse
    const RuleContainer& container = rule.getRuleContainer();
    std::string from = std::get<std::string>(container.ruleInformation.at(RuleField::from));
    int count =  std::get<int>(container.ruleInformation.at(RuleField::count));

    std::shared_ptr<Variable> fromPtr = processToList(from);

    if(fromPtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeDiscard error, type mismatch; not ListType" <<std::endl;
    }

    try{
        for(int i = 0; i < count; ++i){
            fromPtr->listVar.erase(fromPtr->listVar.begin());
        }
    }catch(exception &e){
        LOG(INFO) << "Discard failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeAdd(Rule &rule) {

}

void interpreter::Interpreter::executeTimer(Rule &rule) {

}

void interpreter::Interpreter::processRules(Rule &rule) {

}

void interpreter::Interpreter::executeInputChoice(Rule &rule) {

}

void interpreter::Interpreter::executeInputVote(Rule &rule) {

}

void interpreter::Interpreter::executeInputText(Rule &rule) {

}

void interpreter::Interpreter::executeMessage(Rule &rule) {

}

void interpreter::Interpreter::executeGlobalMessage(Rule &rule) {

}

void interpreter::Interpreter::executeScores(Rule &rule) {

}

