#include "include/gameRules.h"
#include <iostream>

int main() {
    nlohmann::json rulesInJson = nlohmann::json::array();
    rulesInJson["rule"] = "global-message";
    rulesInJson["value"] = "Round {round}. Choose your weapon!";


    //GameRules rules;
    //rules.getGameRules(rulesInJson);
    ///rules.printRules();
    std::cout << rulesInJson << std::endl;

    return 0;
}