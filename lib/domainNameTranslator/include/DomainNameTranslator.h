#ifndef DOMAINNAMETRANSLATOR_H
#define DOMAINNAMETRANSLATOR_H

#include <string>
#include <vector>

namespace domainnametranslator {

    class DomainNameTranslator {
        public:
            // Takes an instruction in the format of variableName.instruction 
            // and parses this instruction.
            // Returns a vector contatining the parsed instruction.
            // E.g. Input = player.name Output = {player,name}
            static std::vector<std::string> parseInstruction(std::string& instruction); 
    };
}

#endif