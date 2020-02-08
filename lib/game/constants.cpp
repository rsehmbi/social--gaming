#include "include/constants.h"
#include <string>
#include <iostream>
#include "include/nodes.h"
#include <vector>

using constants::Constants;
using nodes::Nodes;

//Converts Constants from Json to C++ vector
void ingestConstants(json &data, std::vector<nodes::Nodes> &listOfConstants){
    Nodes node;
    std::map<std::string, std::string> mymap;
    node.constantName=data.begin().key();
    std::vector<mapStringToString> nodeList;
    for (int i=0; i!=data.begin().value().size(); i++) {
        //traverse through all key-value pairs
       for (json::iterator it = data.begin().value()[i].begin(); it != data.begin().value()[i].end(); ++it) {
            mymap[it.key()]=it.value();
            nodeList.push_back(mymap);
        }
    }
    listOfConstants.push_back(node);
}