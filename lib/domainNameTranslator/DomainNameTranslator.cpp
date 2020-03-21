#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

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

//collect for maps ie "players.elements.collect(player, player.weapon == weapon.beats)"
//may need to overload for other types
std::vector<Variable> collect(
            /*PerPlayer& identifier,*/
            const std::string& targetName, 
            const std::string& compareArgs, 
            GameState& state){
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