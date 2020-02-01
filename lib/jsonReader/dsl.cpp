#include "include/dsl.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>
#include <list>

// DSL is currently a stub

dsl::DSL() {
    // Takes a JSON file as an arguement
    // and creates a domain specific language
<<<<<<< HEAD:lib/interpreter/dsl.cpp
}

nlohmann::json DSL::add(json rule){
    json returnObject;
    return returnObject["value"] =  rule["value"].get<int> + rule["to"].get<int>;
}

nlohmann::json inputChoice(const nlohmann::json& h) {
    nlohmann::json returnObject;
    std::cout<<h["prompt"];
    std::cout<<h["choices"];
    printf("\n");
    returnObject["input_needed"]=true;
    returnObject["result"]= {input};
    returnObject["User"]="Player";// the player to request
    return returnObject;
}

nlohmann::json inputText(const nlohmann::json& h) {
    nlohmann::json returnObject;
    std::cout<<h["prompt"];
    //std::cout<<h["choices"];
    printf("\n");
    returnObject["input_needed"]=true;
    returnObject["result"]= {input};
    returnObject["User"]="Player";// the player to request
    return returnObject;
}

nlohmann::json inputVote(const nlohmann::json& h) {
    nlohmann::json returnObject;
    std::list<std::string> listOfPeople ={"a","b","c"};
    for (auto i: listOfPeople){//send message to multiple players in the future
        printf("\n");
        std::cout<<h["prompt"];
    }
    std::cout<<h["choices"];
    printf("\n");
    returnObject["input_needed"]=true;
    returnObject["result"]= {input};
    returnObject["User"]="Player";// the player to request
    return returnObject;
}

nlohmann::json message(const nlohmann::json& h) {
    nlohmann::json returnObject;
    std::list<std::string> listOfPeople ={"a","b","c"};
    for (auto& [key, value] : h.items()) {
        returnObject[key] =value;
    }
    return returnObject;
}

nlohmann::json globalMessage(const nlohmann::json& h) {
    nlohmann::json returnObject;
    returnObject["User"]="Owner";
    std::cout<<h["value"];
}

nlohmann::json scores(const nlohmann::json& h) {
    nlohmann::json returnObject;
    std::cout<<h["score"];
    if (h["key"]==NULL || h["key"]==false){
        //need to figure out how to obtain value from players
        //don't sort
    }
    else {
        //sort ascending
    }
    return returnObject;
}

void updateStatus(); //function to propgate action back to user
=======
};
>>>>>>> production:lib/jsonReader/dsl.cpp
