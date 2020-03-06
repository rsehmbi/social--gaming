#include "Variables.h"

using game::Variables;
using game::VariableVariant;


VariableVariant Variables::getVariable (const std::string& varName) const {
    //for debugging, should not happen
    if(varMap.find(varName) == varMap.end()){
        std::cout << "Interal error: invalid variable error" << std::endl;
    }

    return varMap.at(varName);
}