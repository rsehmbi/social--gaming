#include "include/interpreter.h"

using interpreter::Interpreter;

Interpreter::Interpreter() {
    configureDSL();
}

void Interpreter::configureDSL() {
    // Read JSON file that specifies the DSL
    // Based on the specification, configure the DSL

    // DSL is currently a stub
    language = DSL();
}

void Interpreter::interpretGame() {

}