#include "include/json.hpp"
#include "include/dsl.h"
#include <fstream>
#include <iostream>
#include <list>

int main(){
    printf("Hello World!\n");
    using json = nlohmann::json;
    std::ifstream input("example.json");
    json jsonObject;
    json modifiedInput;
    json modifiedOutput;
    jsonObject<<input;
    std::cout<<jsonObject;
    //printf("\n");
    std::cout<<jsonObject["to"];
    modifiedInput=inputVote(jsonObject);
    std::cout<<modifiedInput;//primitive testing for now
    modifiedOutput=message(jsonObject);
    std::cout<<modifiedOutput;
    return 0;
}