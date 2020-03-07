#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Rule.h"
#include "GameState.h"

using game::Rule;
using game::GameState;

namespace interpreter{

    class Interpreter{
    public:
        void executeGlobalMessageRule(Rule rule);
        void executeMessageRule(Rule rule);

    private:
    };
}

#endif