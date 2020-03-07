#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>

using interpreter::Interpreter;
using namespace game;
using namespace std;


void Interpreter::processRules(json gameRules, json gameData){
    json ruleBlock = getNextRuleBlock(gameRules);
    if(hasNestedRules(ruleBlock)){
        processRules(ruleBlock, gameData);
    }
    //calls processor to process rule block
}

void Interpreter::executeReverse(GameState &state, const Constants &constants, Configurations configurations, std::string listName)
{
    VariableVariant VariableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
        switch (variableType) {
            case VariableType::ListType:
                std::reverse(std::get<ListVariant>(state.variables.getVariable(listName)).begin(),
                std::get<ListVariant>(state.variables.getVariable(listName)).end());
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::reverse(std::get <std::string> (state.variables.getVariable(listName)).begin()
                ,std::get <std::string> (state.variables.getVariable(listName)).end());
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }

}
 
void Interpreter::executeShuffle(GameState &state, const Constants &constants, Configurations configurations, std::string listName)
{
    VariableVariant VariableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       
        switch (variableType) {
            case VariableType::ListType:
                std::shuffle(std::get<ListVariant>(state.variables.getVariable(listName)).begin(),
                std::get<ListVariant>(state.variables.getVariable(listName)).end(),seed);
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::shuffle(std::get <std::string> (state.variables.getVariable(listName)).begin()
                ,std::get <std::string> (state.variables.getVariable(listName)).end(),seed);
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }

}

void Interpreter::executeDeal(GameState &state, const Constants &constants,
                Configurations configurations, int count, int from, int to) {
        // TO DO:
        // Need more information
}

void Interpreter::executeSort(GameState &state, const Constants &constants, Configurations configurations, std::string listName) {
    VariableVariant VariableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
        switch (variableType) {
            case VariableType::ListType:
                std::sort(std::get<ListVariant>(state.variables.getVariable(listName)).begin(),
                std::get<ListVariant>(state.variables.getVariable(listName)).end());
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::sort(std::get <std::string> (state.variables.getVariable(listName)).begin()
                ,std::get <std::string> (state.variables.getVariable(listName)).end());
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }
}

void Interpreter::shuffleList(ListName& list)
{

}

void Interpreter::sortList(ListName& list)
{

}
void Interpreter::dealList(ListName From, ListName To, Count count)
{

}
