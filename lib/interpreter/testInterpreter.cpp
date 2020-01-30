#include "include/json.hpp"
#include <fstream>
#include <iostream>

int main(){
    printf("Hello World!\n");
    using json = nlohmann::json;
    std::ifstream i("example.json");
    json k;
    k<<i;
    std::cout<<k;
    printf("\n");
    std::cout<<k["configuration"];
    return 0;
}