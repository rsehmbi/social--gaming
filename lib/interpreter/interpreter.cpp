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

json Interpreter::getNextRuleBlock(json ruleBlock){
    return NULL;
}

bool Interpreter::hasNestedRules(json ruleBlock){
    return false;
}
