#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

using namespace game;
using domainnametranslator::DomainNameTranslator;

std::string
getVariableFromBrackets(std::string variable, std::string forwardBracket, std::string reverseBracket) {
    unsigned firstLim = variable.find(forwardBracket);
    unsigned lastLim = variable.find(reverseBracket);
    std::string strNew = variable.substr(firstLim,lastLim);
    strNew = strNew.substr(firstLim + 1);
    return strNew;
}

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
    std::string leftCurlyBracket = "{";
    std::string rightCurlyBracket = "}";
    std::string leftParenthesis = "(";
    std::string rightParenthesis = ")";
    // Handles parsing instructions enclosed by curly braces e.g. {player.name}
    if (boost::algorithm::contains(instruction, leftCurlyBracket)) {
        std::string variable = getVariableFromBrackets(instruction, leftCurlyBracket, rightCurlyBracket);
        return parseInstruction(variable);
    }

    std::vector<std::string> result; 
    std::string delimiter = ".";
    std::string instructionWithoutParenthesis = instruction.substr(0, instruction.find(leftParenthesis));
    boost::split(result, instructionWithoutParenthesis, boost::is_any_of(delimiter)); 
    
    // Handles parsing methods and their associated parameters
    // e.g. contains(weapon.name)
    if (boost::algorithm::contains(instruction, leftParenthesis) {
        if (boost::algorithm::contains(instruction, "upfrom")) {
            result.erase(std::remove(result.begin(), result.end(), "upfrom"), result.end());
            // TODO: once we have method to process "upfrom" function, call this method here
        }
        else if (boost::algorithm::contains(instruction, "contains")) {
            result.erase(std::remove(result.begin(), result.end(), "contains"), result.end());
            // TODO: once we have method to process "contains" function, call this method here
        }
        else if (boost::algorithm::contains(instruction, "collect")) {
            result.erase(std::remove(result.begin(), result.end(), "collect"), result.end());
            // TODO: once we have method to process "collect" function, call this method here
        }
    }
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