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
            // Takes an instruction whether in the format of variableName.instruction or
            // variableName.instruction.function(parameters), parses this instruction
            // and calls the appropriate functions for this instruction.
            // Returns a Variable object.
            static Variable parseInstruction(const std::string& instruction, RunningGameState& state); 

            // Takes an instruction and extracts the command chain into a vector.
            // Returns a vector of these command chain instructions.
            // e.g. for "players.elements.collect(player, player.weapon == weapon.beats)"
            // returns {"players", "elements", "collect"}
            static std::vector<std::string> parseCommandChain(std::string instruction);

            // Takes an instruction and extracts the function arguments into a vector.
            // Returns a vector of these function arguments.
            // e.g. for "players.elements.collect(player, player.weapon == weapon.beats)"
            // returns {"player", "player.weapon==weapon.beats"}
            static std::vector<std::string> parseFuncArgs(std::string instruction);
    };
}

#endif