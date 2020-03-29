#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include "GameState.h"

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
Variable evaluate(const std::vector<std::string>& commandChain, 
                const std::vector<std::string>& funcArgs, GameState& state);



//needs to return variable entry point from rules, please update

//Variable
//DomainNameTranslator::parseInstruction(std::string& instruction, GameState& state) {

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
    if (boost::algorithm::contains(instruction, leftParenthesis)) {
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

std::unordered_map<OpType, std::string> opMap{
    {OpType::Equal, "=="},
	{OpType::LessOrEqual, "<="},
	{OpType::GreaterOrEqual, ">="},
	{OpType::Less, "<"},
	{OpType::Greater, ">"},
};

OpType getOpType(const std::string& funcArgs){
    if(funcArgs.find("==") != std::string::npos){
        return OpType::Equal;
    }
    if(funcArgs.find("<=") != std::string::npos){
        return OpType::LessOrEqual;
    }
    if(funcArgs.find(">=") != std::string::npos){
        return OpType::GreaterOrEqual;
    }
    if(funcArgs.find(">") != std::string::npos){
        return OpType::Less;
    }
    if(funcArgs.find("<") != std::string::npos){
        return OpType::Greater;
    }
    std::cout << "Error: operation not support" << std::endl;
    return OpType::Equal;
}

Variable fetchIdentifier(const std::string& identifier, GameState& state){
    std::shared_ptr<Variable> varPtr = state.gameVariables.getVariable(identifier);
    if(identifier == "players"){
        //convert to variable of vector pointer
        Variable players;
        players.varType = VariableType::ListType;
        for(auto& [key, val] : varPtr->mapVar){
            players.listVar.push_back(val);
        }
        return players;
    }
    std::cout << "Error: identifer not supported" << std::endl;
    return Variable();
}

std::vector<std::string> getFuncOperands(const std::string& funcArgs, OpType op){
    std::vector<std::string> result; 
    std::string delimiter = opMap.at(op);
    boost::split(result, funcArgs, boost::is_any_of(delimiter));
    //remove white spaces
    for(auto& s : result){
        s.erase( std::remove_if(s.begin(), s.end(), ::isspace ), s.end());
    }
    return result;
}

//collect for maps ie "players.elements.collect(player, player.weapon == weapon.beats)"

//currently only specialized for player.weapon == weapon.beats
//TODO generalize to other commands
Variable collect(Variable& list, const std::vector<std::string>& funcArgs, GameState& state){
    std::string elementName = funcArgs[0];
    OpType operation = getOpType(funcArgs[1]);
    std::vector<std::string> operands = getFuncOperands(funcArgs[1], operation);
    Variable result;
    result.varType = VariableType::ListType;


    //register list to name so subsequent parseInstruction calls will be able to find the element
    
    std::vector<VariablePtr> listVar = list.listVar;
    for(auto& elementPtr : listVar){
        state.gameVariables.createVariable(elementName, elementPtr);
        Variable lhs = DomainNameTranslator::parseInstruction(operands[0], state);
        Variable rhs = DomainNameTranslator::parseInstruction(operands[1], state);
        if(compare(lhs.stringVar, rhs.stringVar)){
            result.listVar.push_back(elementPtr);
        }
    }
    return result;
}

//evaluates output from parseInstructions
//eg "players.elements.collect(player, player.weapon == weapon.beats)":
//commandChain = {"players", "elements", "collect"}, funcArgs = {player, player.weapon == weapon.beats}
Variable evaluate(const std::vector<std::string>& commandChain, 
                const std::vector<std::string>& funcArgs, GameState& state){
    //check identifier
    Variable identifier = fetchIdentifier(commandChain[0], state);
    if(commandChain[2] == "elements"){
        if(commandChain[3] == "collect"){
            Variable result = collect(identifier, funcArgs, state);
            return result;
        }
    }

}

