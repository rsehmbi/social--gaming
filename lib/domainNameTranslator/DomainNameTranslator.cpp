#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

using domainnametranslator::DomainNameTranslator;

std::string
getVariableFromBrackets(std::string variable, std::string forwardBracket, std::string reverseBracket) {
    unsigned firstLim = variable.find(forwardBracket);
    unsigned lastLim = variable.find(reverseBracket);
    std::string strNew = variable.substr(firstLim,lastLim);
    strNew = strNew.substr(firstLim + 1);
    return strNew;
}

std::vector<std::string>
DomainNameTranslator::parseInstruction(std::string& instruction) {
    // Handles parsing instructions enclosed by curly braces e.g. {player.name}
    if (boost::algorithm::contains(instruction, "{")) {
        std::string variable = getVariableFromBrackets(instruction, "{", "}");
        return parseInstruction(variable);
    }

    std::vector<std::string> result; 
    std::string delimiter = ".";
    std::string instructionWithoutParenthesis = instruction.substr(0, instruction.find("("));
    boost::split(result, instructionWithoutParenthesis, boost::is_any_of(delimiter)); 
    
    // Handles parsing methods and their associated parameters
    // e.g. contains(weapon.name)
    if (boost::algorithm::contains(instruction, "(")) {
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