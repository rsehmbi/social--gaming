#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Rule.h"
#include "GameState.h"

using game::Rule;
using game::GameState;

namespace interpreter{

    class Interpreter{
    public:
        GameState executeGlobalMessageRule(Rule rule, GameState state);

    private:
    };
}

#endif