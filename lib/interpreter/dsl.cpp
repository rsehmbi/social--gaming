#include "include/dsl.h"

#include <fstream>
#include <iostream>

DSL::DSL() {
    // Takes a JSON file as an arguement
    // and creates a domain specific language
}

json DSL::extend(json rules) {
    json returnObj;
    returnObj["target"] = rules["target"];

    int listSize = rules["list"].size();
    for(int i = 0; i < listSize; i++) {
        returnObj["target"].emplace_back(rules["list"][i]);
    }

    return returnObj;
}

json DSL::reverse(json rules) {
    json returnObj;
    auto list = rules["list"];
    std::cout << list << std::endl;

    return returnObj;
}


int main() {
    json obj;
    obj["list"] = json::array({"player1", "player2", "player3"});

    DSL::reverse(obj);
    return 0;
}