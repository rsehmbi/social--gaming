#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include "GameState.h"
#include <iostream>

using domainnametranslator::DomainNameTranslator;


std::string
getVariableFromBrackets(std::string variable, std::string forwardBracket, std::string reverseBracket) {
    unsigned firstLim = variable.find(forwardBracket);
    unsigned lastLim = variable.find(reverseBracket);
    std::string strNew = variable.substr(firstLim,lastLim);
    boost::erase_all(strNew, forwardBracket);
    boost::erase_all(strNew, reverseBracket);
    strNew.erase(std::remove_if(strNew.begin(), strNew.end(), ::isspace ), strNew.end());
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
Variable
evaluate(std::vector<std::string> commandChain, 
                const std::vector<std::string>& funcArgs, GameState& state);

Variable
evaluateBinaryOperationCommand(const std::string& compareStatement, GameState& state);


std::vector<std::string>
DomainNameTranslator::parseCommandChain(std::string instruction) {
    std::string leftCurlyBracket = "{";
    std::string rightCurlyBracket = "}";
    std::string leftParenthesis = "(";
    std::string rightParenthesis = ")";
    // Handles parsing instructions enclosed by curly braces e.g. {player.name}
    if (boost::algorithm::contains(instruction, leftCurlyBracket)) {
        std::string variable = getVariableFromBrackets(instruction, leftCurlyBracket, rightCurlyBracket);
        return parseCommandChain(variable);
    }

    std::vector<std::string> result; 
    std::string delimiter = ".";
    std::string instructionWithoutParenthesis = instruction.substr(0, instruction.find(leftParenthesis));
    boost::split(result, instructionWithoutParenthesis, boost::is_any_of(delimiter)); 

    return result;
}

std::vector<std::string>
DomainNameTranslator::parseFuncArgs(std::string instruction) {
    std::string leftParenthesis = "(";
    std::string rightParenthesis = ")";
    std::string variable = getVariableFromBrackets(instruction, leftParenthesis, rightParenthesis);
    std::vector<std::string> result; 
    std::string delimiter = ",";
    boost::split(result, variable, boost::is_any_of(delimiter)); 
    return result;
}


//TODO: add support for "winners.size == players.size" by
Variable
DomainNameTranslator::parseInstruction(const std::string& instruction, GameState& state) {

    if(1){
        //case with operators (==, <=, ...) AND no brackets ie: "winners.size == players.size"
        //can directly call evaluateBinaryOperationCommand
        Variable result = evaluateBinaryOperationCommand(instruction, state);
        return result;
    }

    std::vector<std::string> commandChain = parseCommandChain(instruction);
    std::vector<std::string> funcArgs = parseFuncArgs(instruction);
    Variable result = evaluate(commandChain, funcArgs, state);
    
    return result;
}

//comparator for each "player.weapon == weapon.beats"
//restrict to string, bool, or int
bool
compare(const std::string& lhs, const std::string& rhs){
    //can only be OpType::Equal
    return lhs == rhs;
}

bool
compare(bool lhs, bool rhs){
    //can only be OpType::Equal
    return lhs == rhs;
}

bool
compare(int lhs, int rhs, OpType optype){
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

std::unordered_map<OpType, std::string>
opMap{
    {OpType::Equal, "=="},
	{OpType::LessOrEqual, "<="},
	{OpType::GreaterOrEqual, ">="},
	{OpType::Less, "<"},
	{OpType::Greater, ">"},
};

OpType
getOpType(const std::string& funcArgs){
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

std::vector<std::string>
getFuncOperands(const std::string& funcArgs, OpType op){
    std::vector<std::string> result; 
    std::string delimiter = opMap.at(op);
    boost::split(result, funcArgs, boost::is_any_of(delimiter));
    //remove white spaces
    for(auto& s : result){
        s.erase( std::remove_if(s.begin(), s.end(), ::isspace ), s.end());
    }
    return result;
}

Variable evaluateBinaryOperationCommand(const std::string& compareStatement, GameState& state){
    OpType operation = getOpType(compareStatement);
    std::vector<std::string> operands = getFuncOperands(compareStatement, operation);
    Variable lhs = DomainNameTranslator::parseInstruction(operands[0], state);
    Variable rhs = DomainNameTranslator::parseInstruction(operands[1], state);
    Variable result;
    result.varType = VariableType::BoolType;

    switch(lhs.varType) {
        case VariableType::StringType: 
        {
            result.boolVar = compare(lhs.stringVar, rhs.stringVar);
        } break;
        default:
            std::cout << "evaluateBinaryOperationCommand unsupported type, please implement";
            return Variable();
    }

    return result;
}

std::shared_ptr<Variable>
collect(std::shared_ptr<Variable> list, const std::vector<std::string>& funcArgs, GameState& state){

    
    std::shared_ptr<Variable> result = std::make_shared<Variable>();
    result->varType = VariableType::ListType;

    for(auto& varPtr : list->listVar){
        //register list to name so subsequent parseInstruction calls will be able to find the element
        state.gameVariables.updateVariable(funcArgs[0], varPtr);

        //expect true or false
        Variable validator = DomainNameTranslator::parseInstruction(funcArgs[1], state);

        if(validator.boolVar == true){
            result->listVar.push_back(varPtr);
        }
    }

    state.gameVariables.removeVariable(funcArgs[0]);
    return result;
}

std::shared_ptr<Variable>
identify(const std::string& identifier, GameState& state){
    std::shared_ptr<Variable> varPtr = state.gameVariables.getVariable(identifier);
    return varPtr;
}

std::shared_ptr<Variable>
modify(std::shared_ptr<Variable> varPtr, const std::string& modifier, GameState& state){
    if(modifier == "elements"){
        if(varPtr->varType == VariableType::MapType){
            std::shared_ptr<Variable> flattened = std::make_shared<Variable>();
            flattened->varType = VariableType::ListType;
            for(auto& [key, val] : varPtr->mapVar){
                flattened->listVar.push_back(val);
            }
            return flattened;
        } else {return varPtr;}        
    }
    std::cout << "Error: identifer not supported" << std::endl;
    return nullptr;
}

std::shared_ptr<Variable>
performFunction(std::shared_ptr<Variable> varPtr,
                const std::string& funcName,
                const std::vector<std::string>& funcArgs,
                GameState& state){
    
    if(funcName == "collect"){
        return collect(varPtr, funcArgs, state);
    }
    std::cout << "Error: identifer not supported" << std::endl;
    return nullptr;
}


//evaluates output from parseInstructions
//eg "players.elements.collect(player, player.weapon == weapon.beats)":
//commandChain = {"players", "elements", "collect"}, funcArgs = {player, player.weapon == weapon.beats}
Variable
evaluate(std::vector<std::string> commandChain, 
                const std::vector<std::string>& funcArgs, GameState& state){
    
    std::string funcName;
    //dealing with function
    if(!funcArgs.empty()){
        funcName = commandChain.back();
        commandChain.pop_back();
    }
    //evaluate chain
    std::shared_ptr<Variable> resultPtr = identify(commandChain[0], state);
    auto it = commandChain.begin();
    std::advance(it, 1);
    while(it != commandChain.end()){
        resultPtr = modify(resultPtr, *it, state);
        it++;
    }
    
    if(!funcArgs.empty()){
        resultPtr = performFunction(resultPtr, funcName, funcArgs, state);
    }

    return *resultPtr;
}

