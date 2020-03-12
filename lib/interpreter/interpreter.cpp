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
                // std::shuffle(std::get<ListVariant>(variableVariant).begin(), ////**** not working
                // std::get<ListVariant>(variableVariant).end(),seed); ////**** not working
                break;
            case VariableType::BoolType:
                break;
            case VariableType::StringType:
                // std::shuffle(std::get <std::string> (variableVariant).begin() ////**** not working
                // ,std::get <std::string> (variableVariant).end(),seed); ////**** not working
                break;
            case VariableType::MapType:
                break;
            case VariableType::NumberType:
                break;
        }

}

void Interpreter::executeDeal(GameState &state, const Constants &constants,
                Configurations &configurations, Count count, ListName &from, ListName &to) {////**** fixed not matched with header
        // TO DO:
        // Need more information
}

void Interpreter::executeDiscard(GameState &state, const Constants &constants,
                Configurations &configurations, Count count, ListName &from) {
                //checks if list not empty
                //checks count smaller-equal list
                //copy list into vector
                //use erase function in vector
}
void Interpreter::executeListAttributes(GameState &state, const Constants &constants,
                Configurations &configurations, ListName &list, ListType &type) {
                    
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
    // int intVariable = std::get<int>(std::get<game::ListVariant>(variableVariant));////**** replaced with below line
    int intVariable = std::get<int>(variableVariant); 

    // if value is just an integer
    if (!value.empty() && (std::find_if(value.begin(), value.end(), [](unsigned char c) { return !std::isdigit(c); }) == value.end())) { ////**** fixed had extra ;
        intVariable += std::stoi(value);
    } else
    {
        // if value is a name of a Constant
        VariableVariant valueVariable = state.variables.getVariable(value); 
        // int intValue = std::get<int>(std::get<game::ListVariant>(valueVariable));////**** eplaced with below line
        int intValue = std::get<int>(variableVariant);      
        intVariable += intValue;
    }
}

void Interpreter::executeTimer(GameState& state, VariableName& value) {
    // TODO: need to build bridge between game execution and server first
}

void Interpreter::executeInputChoice(const Constants &constants, GameSession& session, Input& to, Input& prompt, 
                                        Input& choices, Input& result, Count& timeout){
    std::optional<Count> isTimeOut= timeout;
    if (!isTimeOut){
        for (auto player: session.getPlayers()){
            if (player.getName==to){
                session.msgConnection(player.getConnectionID, prompt);
            }
            //otherwise do nothing
        }
        /*
        std::vector<game::Player>::iterator it=std::find_if(
            state.playerList.begin(), state.playerList.end(), 
            [](const game::Player& i, Input& to) {return true;});//i.getConnectionID()==to.getConnectionID();};
        //PlayerID connection = state.playerList.getVariable(toVariable); 
        session.msgConnection(it.getConnectionID(), prompt);

/*
GameSession::msgConnection(const ConnectionID& target, const std::string& msg){
    outMsgs.push_back({target, msg});
}
*/

    }
    else{
        //TimeoutRoute
    }
}


/*
 Input to;
        Input prompt;
        Input choices;
        Input result;
        Count timeout;
*/