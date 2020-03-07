#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>
#include <string>

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

void Interpreter::executeReverse(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName)
{
    VariableVariant variableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
        switch (variableType) {
            case VariableType::ListType:
                std::reverse(std::get<ListVariant>(variableVariant).begin(),
                std::get<ListVariant>(variableVariant).end());
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::reverse(std::get <std::string> (variableVariant).begin()
                ,std::get <std::string> (variableVariant).end());
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }

}
 
void Interpreter::executeShuffle(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName)
{
    VariableVariant variableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       
        switch (variableType) {
            case VariableType::ListType:
                std::shuffle(std::get<ListVariant>(variableVariant).begin(),
                std::get<ListVariant>(variableVariant).end(),seed);
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::shuffle(std::get <std::string> (variableVariant).begin()
                ,std::get <std::string> (variableVariant).end(),seed);
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }

}

void Interpreter::executeDeal(GameState &state, const Constants &constants,
                Configurations configurations, Count count, ListName &from, ListName &to) {
        // TO DO:
        // Need more information
}

void Interpreter::executeSort(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName) {
    VariableVariant variableVariant = state.variables.getVariable(listName);
    VariableType variableType = state.variables.getVariableType(listName);
        switch (variableType) {
            case VariableType::ListType:
                std::sort(std::get<ListVariant>(variableVariant).begin(),
                std::get<ListVariant>(variableVariant).end());
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                std::sort(std::get <std::string> (variableVariant).begin()
                ,std::get <std::string> (variableVariant).end());
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }
}

void Interpreter::executeAdd(GameState& state, VariableName& toVariable, VariableName& value) {
    VariableVariant variableVariant = state.variables.getVariable(toVariable);
    int intVariable = std::get<int>(std::get<game::ListVariant>(variableVariant);

    // if value is just an integer
    if (!value.empty() && std::find_if(value.begin(), value.end(), [](unsigned char c) { return !std::isdigit(c); }) == value.end();) {
        intVariable += std::stoi(value);
    } else
    {
        // if value is a name of a Constant
        VariableVariant valueVariable = state.variables.getVariable(value);
        int intValue = std::get<int>(std::get<game::ListVariant>(valueVariable);
        intVariable += intValue;
    }
}

void Interpreter::executeTimer(GameState& state, VariableName& value) {
    // TODO: need to build bridge between game execution and server first
}

