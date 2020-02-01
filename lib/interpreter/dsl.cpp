#include "include/dsl.h"
#include "include/json.hpp"
#include <fstream>
#include <iostream>
#include <list>

// DSL is currently a stub

DSL::DSL() {
    // Takes a JSON file as an arguement
    // and creates a domain specific language
}

nlohmann::json inputChoice(nlohmann::json h) {
    nlohmann::json returnObject;
    std::cout<<h["prompt"];
    std::cout<<h["choices"];
    printf("\n");
    returnObject["input_needed"]=true;
    returnObject["result"]= {input};
    returnObject["User"]="Player";// the player to request
    return returnObject;
}

nlohmann::json inputText(nlohmann::json h) {
    nlohmann::json returnObject;
    std::cout<<h["prompt"];
    //std::cout<<h["choices"];
    printf("\n");
    returnObject["input_needed"]=true;
    returnObject["result"]= {input};
    returnObject["User"]="Player";// the player to request
    return returnObject;
}

nlohmann::json inputVote(nlohmann::json h) {
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

nlohmann::json message(nlohmann::json h) {
    nlohmann::json returnObject;
    std::list<std::string> listOfPeople ={"a","b","c"};
    for (auto& [key, value] : h.items()) {
        returnObject[key] =value;
    }
    return returnObject;
}

nlohmann::json globalMessage(nlohmann::json h) {
    nlohmann::json returnObject;
    returnObject["User"]="Owner";
    std::cout<<h["value"];
}

nlohmann::json scores(nlohmann::json h) {
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
