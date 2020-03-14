#include "Variables.h"

using game::Variable;
using game::Variables;
using game::VariableType;


std::shared_ptr<Variable> Variables::getVariable (const std::string& varName) const {
    //for debugging, should not happen
    if(variables.find(varName) == variables.end()){
        std::cout << "Interal error: invalid variable error" << std::endl;
    }
    return variables.at(varName);
}

void Variables::createVariable (const std::string& key, std::shared_ptr<Variable> val) {
        if(variables.find(key) != variables.end()){
            std::cout << "Interal error: key already exists. use getVariable to modify instead" << std::endl;
        } else{
            variables.emplace(key, std::move(val));
        }
}
