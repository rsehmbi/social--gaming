#ifndef DOMAINNAMETRANSLATOR_H
#define DOMAINNAMETRANSLATOR_H

#include "Game.h"
#include <string>
#include <vector>
#include <iostream>

using namespace game;

namespace domainnametranslator {

    class DomainNameTranslator {
        public:
            // Takes an instruction in the format of variableName.instruction 
            // and parses this instruction.
            // Returns a vector contatining the parsed instruction.
            // E.g. Input = player.name Output = {player,name}
            static Variable parseInstruction(std::string& instruction, GameState& state); 
    };
}

#endif