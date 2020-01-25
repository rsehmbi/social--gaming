#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "include/dsl.h"

namespace interpreter {

    // The Interpreter class is responsible for interpreting
    // game rules that are specified in a JSON file
    class Interpreter {
    public:
        Interpreter();
        ~Interpreter();

        // Takes JSON file that specifies a game
        void interpretGame();

    private:
        DSL::DSL language;
        
        // Reads the specifications for the domain specific language
        void configureDSL();
    };
}

#endif