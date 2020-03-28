#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include "GameState.h"

using namespace game;
using domainnametranslator::DomainNameTranslator;

enum class OpType{
    GreaterOrEqual,
    Greater,
    LessOrEqual,
    Less,
    Equal
};


/*
Notes: example command: 
"players.elements.collect(player, player.weapon == weapon.beats)"
*/
//needs to return variable
std::vector<std::string>
DomainNameTranslator::parseInstruction(std::string& instruction) {
    std::vector<std::string> result; 
    std::string delimiter = ".";
    boost::split(result, instruction, boost::is_any_of(delimiter)); 
    return result;
}

//comparator for each "player.weapon == weapon.beats"
//restrict to string, bool, or int
bool compare(const std::string& lhs, const std::string& rhs){
    //can only be OpType::Equal
    return lhs == rhs;
}

bool compare(bool lhs, bool rhs){
    //can only be OpType::Equal
    return lhs == rhs;
}

bool compare(int lhs, int rhs, OpType optype){
    switch(optype) {
        case OpType::Equal: 
        {
            return lhs == rhs;
        }
        case OpType::Less: 
        {
            return lhs < rhs;
        }
        case OpType::LessOrEqual: 
        {
            return lhs <= rhs;
        }
        case OpType::Greater: 
        {
            return lhs > rhs;
        }
        case OpType::GreaterOrEqual: 
        {
            return lhs >= rhs;
        }
        default:
            std::cout << "unsupported int OpType";
            return false;
    }
}

Variable* fetchIdentifier(std::string& identifier; GameState& state){
    Variable* varPtr = state.gameVariables.getVariable(identifier);
    std::vector<Variable*> playerVariables;
    return playerVariables;
}

//evaluates output from parseInstructions
//eg "players.elements.collect(player, player.weapon == weapon.beats)":
//commandChain = {"players", "elements", "collect"}, funcArgs = {player, player.weapon == weapon.beats}
Variable evaluate(const std::vector<std::string>& commandChain, 
                const std::vector<std::string>& funcArgs, GameSate& state){
    //check identifier
    std::vector<Variable*> identifier = fetchIdentifier(commandChain[0], state);
    if(commandChain[3] == "collect"){
        collect(playerElements, funcArgs);
    }

}

//collect for maps ie "players.elements.collect(player, player.weapon == weapon.beats)"
//may need to overload for other types
Variable collect(std::vector<Variable*> list, const std::vector<std::string>& funcArgs, GameState& state){
    std::string elementName = funcArgs[0];
    //TODO split player.weapon == weapon.beats to 3 parts and convert to Variable
    Variable lhs;
    Variable rhs;
    OpType comparison;

    
    if(lhs.varType == VariableType::StringType){

    }

    Variable lhs 
    VariablePtr varPtr = std::make_shared<Variable>();
    varPtr->varType = VariableType::PlayerIteratorType;
    // var->playerIterator = identifier.begin();

    //store variable : "player" : Iterator Variable
    state.variables.createVariable(targetName, varPtr);
    
    //TODO
    // while(){

    // }
    
    return std::vector<Variable>();
}