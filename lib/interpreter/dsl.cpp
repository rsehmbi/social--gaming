#include "include/dsl.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>

// DSL is currently a stub

DSL::DSL() {
    // Takes a JSON file as an arguement
    // and creates a domain specific language
}

json DSL::add(json rule){
    json returnObject;
    return returnObject["value"] =  rule["value"].get<int> + rule["to"].get<int>;
}

