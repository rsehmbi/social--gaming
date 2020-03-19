#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <chrono>

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

// // void Interpreter::executeReverse(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName)
// // {
// //     VariableType variableType = state.variables.getVariableType(listName);
// //         switch (variableType) {
// //             case VariableType::ListType:
// //                 std::reverse(std::get<ListVariant>(state.variables.getVariable(listName)).begin(),
// //                              std::get<ListVariant>(state.variables.getVariable(listName)).end());
// //                 break;
// //             case VariableType::BoolType:
// //                 break;
// //             case VariableType::StringType:
// //                 std::reverse(std::get<std::string>(state.variables.getVariable(listName)).begin()
// //                 ,std::get <std::string> (state.variables.getVariable(listName)).end());
// //                 break;
// //             case VariableType::MapType:
// //                 break;
// //             case VariableType::NumberType:
// //                 break;
// //         }
// // }
 
// // void Interpreter::executeShuffle(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName)
// // {
// //     VariableVariant variableVariant = state.variables.getVariable(listName);
// //     VariableType variableType = state.variables.getVariableType(listName);
// //     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       
// //         switch (variableType) {
// //             case VariableType::ListType:
// //                 // std::shuffle(std::get<ListVariant>(variableVariant).begin(), ////**** not working
// //                 // std::get<ListVariant>(variableVariant).end(),seed); ////**** not working
// //                 break;
// //             case VariableType::BoolType:
// //                 break;
// //             case VariableType::StringType:
// //                 // std::shuffle(std::get <std::string> (variableVariant).begin() ////**** not working
// //                 // ,std::get <std::string> (variableVariant).end(),seed); ////**** not working
// //                 break;
// //             case VariableType::MapType:
// //                 break;
// //             case VariableType::NumberType:
// //                 break;
// //         }

// // }

// // void Interpreter::executeDeal(GameState &state, const Constants &constants,
// //                 Configurations &configurations, Count count, ListName &from, ListName &to) {////**** fixed not matched with header
// //         // TO DO:
// //         // Need more information
// // }

// // void Interpreter::executeSort(GameState &state, const Constants &constants, Configurations &configurations, ListName &listName) {
// //     VariableVariant variableVariant = state.variables.getVariable(listName);
// //     VariableType variableType = state.variables.getVariableType(listName);
// //         switch (variableType) {
// //             case VariableType::ListType:
// //                 std::sort(std::get<ListVariant>(variableVariant).begin(),
// //                 std::get<ListVariant>(variableVariant).end());
// //                 break;
// //             case VariableType::BoolType:
// //                 break;
// //             case VariableType::StringType:
// //                 std::sort(std::get <std::string> (variableVariant).begin()
// //                 ,std::get <std::string> (variableVariant).end());
// //                 break;
// //             case VariableType::MapType:
// //                 break;
// //             case VariableType::NumberType:
// //                 break;
// //         }
// // }

// void Interpreter::executeAdd(GameState& state, VariableName& toVariable, VariableName& value) {
//     VariableVariant variableVariant = state.variables.getVariable(toVariable); 
//     // int intVariable = std::get<int>(std::get<game::ListVariant>(variableVariant));////**** replaced with below line
//     int intVariable = std::get<int>(variableVariant); 

//     // if value is just an integer
//     if (!value.empty() && (std::find_if(value.begin(), value.end(), [](unsigned char c) { return !std::isdigit(c); }) == value.end())) { ////**** fixed had extra ;
//         intVariable += std::stoi(value);
//     } else
//     {
//         // if value is a name of a Constant
//         VariableVariant valueVariable = state.variables.getVariable(value); 
//         // int intValue = std::get<int>(std::get<game::ListVariant>(valueVariable));////**** eplaced with below line
//         int intValue = std::get<int>(variableVariant);      
//         intVariable += intValue;
//     }
// }

// void Interpreter::executeTimer(GameState& state, VariableName& value) {
//     // TODO: need to build bridge between game execution and server first
// }

std::shared_ptr<Variable> processToList(std::string domainLanguage){
    //TODO: implement the evaluation of command such as
    // !players.elements.weapon.contains(weapon.name) To a vector.
    // DomainNameTranslator's job?
    std::shared_ptr<Variable> listVariablePtr = std::make_shared<Variable>();
    listVariablePtr->varType = VariableType::ListType;

    return listVariablePtr;
}

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

