#include "include/DomainNameTranslator.h"
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>

using domainnametranslator::DomainNameTranslator;

std::vector<std::string>
DomainNameTranslator::parseInstruction(std::string& instruction) {
    std::vector<std::string> result; 
    std::string delimiter = ".";
    boost::split(result, instruction, boost::is_any_of(delimiter)); 
    return result;
}