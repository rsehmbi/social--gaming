#include "include/Variables.h"

using game::Variables;


Variables::Variables()
    :variables()
{}

Variables::Variables(const std::vector<Element>& variables){
}

const std::vector<game::Element>
Variables::getVariables(){
    return this->variables;
}