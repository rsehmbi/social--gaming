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

void Interpreter::executeReverse(GameState &state, const Constants &constants, Configurations configurations, ListName listName)
{
    auto variable = state.variables.getVariable(listName);
    //This is a prototype of the method not actual implementation.
    switch ((typeid(variable)) {
        case typeid(ListVariant):
            std::reverese(variable.begin(), variable.end());
            //Same for List and String

            break;
        case typeid(std::string):
            std::reverse (variable.begin(), variable.end());
            break;
        case typeid(int):
            // handle Case for more different types
            break;
        default:
            // handle that case
    }

}

void Interpreter::executeShuffle(GameState &state, const Constants &constants, Configurations &configurations, ListName listName) {
    auto variable = state.variables.getVariable(listName);
    // Variables can be of different types
    // Different types needs to shuffled differently
    switch ((typeid(variable)) {
        case typeid(ListVariant):
            std::random_shuffle (variable.begin(), variable.end());
            //Same for List and String
            break;
        case typeid(std::string):
            std::random_shuffle (variable.begin(), variable.end());
            break;
        case typeid(int):
            // handle Case for more different types
            break;
        default:
            // handle that case
    }
}

void Interpreter::executeDeal(GameState &state, const Constants &constants, Configurations &configurations,
        ListName listName) {
        // TO DO:
        // Need more information
}

void Interpreter::executeSort(GameState &state, const Constants &constants, Configurations &configurations, ListName listName) {
    auto variable = state.variables.getVariable(listName);

    // Variables can be of different types
    // Different types needs to sorted differently
    switch ((typeid(variable)) {
        case typeid(ListVariant):
            std::sort( myvector.begin(), myvector.end());
            break;
        case typeid(std::string):
            std::sort( myvector.begin(), myvector.end());
            break;
        case typeid(int):
            // handle that case
            break;
        default:
            // handle that case

}

