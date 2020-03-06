#include "include/interpreter.h"
#include "include/json.hpp"

using interpreter::Interpreter;

Interpreter::Interpreter(json data, json rules)
    : gameRules(rules), gameData(data);

json Interpreter::getUpdate(){
    return this-> gameData;
}

void Interpreter::processRules(json gameRules, json gameData){
    json ruleBlock = getNextRuleBlock(gameRules);
    if(hasNestedRules(ruleBlock)){
        processRules(ruleBlock, gameData);
    }
    //calls processor to process rule block
}

void Interpreter::executeShuffle(GameState &state, const Constants &constants, Configurations &configurations, ListName listName) {

}

void Interpreter::executeDeal(GameState &state, const Constants &constants, Configurations &configurations, ListName listName) {

}

void Interpreter::executeSort(GameState &state, const Constants &constants, Configurations &configurations, ListName listName) {

}

