#include "Variables.h"
#include <glog/logging.h>

using game::Variable;
using game::Variables;
using game::VariableType;
using game::VaribaleCloner;


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


void Variables::removeVariable (const std::string& key) {
        if(variables.find(key) == variables.end()){
            std::cout << "Interal error: key does not exist. use getVariable to modify instead" << std::endl;
        } else{
            variables.erase(key);
        }

void 
VaribaleCloner::copyVariables(const game::VariablePtr& from, std::shared_ptr<Variable> to){
    to->varType = from->varType;
    switch (from->varType){
         case VariableType::NumberType: 
        {
            to->intVar = from->intVar;
            break;
        }
        case VariableType::StringType: 
        {
            to->stringVar = from->stringVar;
            break;
        }
        case VariableType::BoolType: 
        {
            to->boolVar = from->boolVar;
            break;
        }             
        case VariableType::ListType:
        {
            //recursively call convertVariableHelperJSON to process each element in list
            for(const auto& element : from->listVar){
                std::shared_ptr<Variable> elementPtr = std::make_shared<Variable>();
                copyVariables(element, elementPtr);
                to->listVar.push_back(std::move(elementPtr));
            }
            break;
        }
        case VariableType::MapType:
        {
            //recursively call convertVariableHelperJSON to process each element in list
            for(const auto& element : from->mapVar){
                std::shared_ptr<Variable> elementPtr = std::make_shared<Variable>();
                copyVariables(element.second, elementPtr);
                to->mapVar[element.first] = std::move(elementPtr);
            }
            break;
        }
        default:
            LOG(ERROR) << "unsupported valType, please implement";
    }

}