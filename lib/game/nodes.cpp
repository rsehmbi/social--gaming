#include "include/nodes.h"
#include <string>
#include <iostream>

using nodes::Nodes;

void Nodes::setConstantName(std::string constantName){
    this->constantName=constantName;
}

std::string Nodes::getConstantName() const{
    return this->constantName;
}