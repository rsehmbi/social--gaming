#include "include/json.hpp"
#include "include/dsl.h"
#include <fstream>
#include <iostream>
#include <list>

int main(){
    printf("Hello World!\n");
    using json = nlohmann::json;
    std::ifstream i("example.json");
    json k;
    json modifiedInput;
    json modifiedOutput;
    k<<i;
    std::cout<<k;
    //printf("\n");
    std::cout<<k["to"];
    modifiedInput=inputVote(k);
    std::cout<<modifiedInput;//primitive testing for now
    modifiedOutput=message(k);
    std::cout<<modifiedOutput;
    return 0;
}