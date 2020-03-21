#include "include/json.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <map>

int main(){
    printf("Hello World!\n");
    using json = nlohmann::json;
    std::ifstream input("example.json");
    json jsonObject;
    json modifiedInput;
    json modifiedOutput;
    jsonObject<<input;
    std::cout<<jsonObject;
    printf("\n");
    printf("\n");
    std::cout<<jsonObject.begin().value()[0]<< '\n';
    std::map<std::string, std::string> mymap;
    //modifiedInput=jsonObject.begin().value();
    //std::cout<<modifiedInput.value();

    for (auto& element : jsonObject) {
        std::cout << element << '\n';
        for (auto& i : element) {
            std::cout << i << '\n';
            for (auto& [key, value] : i.items()) {
                std::cout << key << " : " << value << "\n";
                std::map<std::string, std::string> (key())=it.value();
            }   
        }
    }

    /*
    printf("\n");
    std::list<std::map<std::string, std::string>> listOfAttributes;
    //for (auto const& value: jsonObject.begin().value().size())
    for (int i=0; i!=jsonObject.begin().value().size(); i++) {
       for (json::iterator it = jsonObject.begin().value()[i].begin(); it != jsonObject.begin().value()[i].end(); ++it) {
       std::cout << it.key() << " : " << it.value() << "\n";
       mymap[it.key()]=it.value();
       //std::map<std::string, std::string> (it.key())=it.value();
       listOfAttributes.push_back(mymap);
        }
    }
    //cout<<listOfAttributes;
    */
    return 0;
}