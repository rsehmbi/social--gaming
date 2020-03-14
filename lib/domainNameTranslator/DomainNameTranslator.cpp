#include "include/DomainNameTranslator.h"

using domainnametranslator::DomainNameTranslator;

std::vector<std::string>
DomainNameTranslator::parseInstruction(std::string& instruction) {
    std::string delimiter = ".";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = instruction.find (delimiter, pos_start)) != std::string::npos) {
        token = instruction.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (instruction.substr (pos_start));
    return res;
}