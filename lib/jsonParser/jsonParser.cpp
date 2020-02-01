#include "include/jsonParser.h"

using json = nlohmann::json;


json jsonParser::JsonParser::createGame(std::string_view specJsonPath, std::string_view configJsonPath){
    json jsonSpecs = readGameSpecification(specJsonPath);
    if (jsonSpecs != nullptr){
        json jsonGame = readGameConfiguration(jsonSpecs, configJsonPath);
        if (ValidateGameJson(jsonGame)){
            return jsonGame;
        } else {
            return nullptr ;
        }
        return jsonGame;
    } else{
        return nullptr;
    }
}

json jsonParser::JsonParser::readGameSpecification(std::string_view jsonSpecPath){
    try{
        std::ifstream inStream(std::string(jsonSpecPath).c_str());
        if (inStream.is_open()) {
            json jsonSpecs;
            inStream >> jsonSpecs;
            return jsonSpecs;
        } else {
            std::cerr << "Could not open specs file. Error: " << strerror(errno) << std::endl;
        }
        return nullptr;
    } catch (const std::exception& e){
        std::cout << "Caught exception " << e.what() << std::endl;
    }
    return nullptr;
}

json jsonParser::JsonParser::readGameConfiguration(json jsonSpecs, std::string_view jsonConfigPath){
    try{
        std::ifstream inStream(std::string(jsonConfigPath).c_str());
        if (inStream.is_open()) {
            json jsonConfig;
            inStream >> jsonConfig;
            jsonSpecs["configuration"] = jsonConfig["configuration"];
            return jsonSpecs;
        } else {
            std::cerr << "Could not open configs file. Error: " << strerror(errno) << std::endl;
        }
        return nullptr;
    } catch (const std::exception& e){
        std::cout << "Caught exception with message: " << e.what() << std::endl;
    } 
    return nullptr;
}

bool jsonParser::JsonParser::ValidateGameJson(json jsonGame){
    if (jsonGame == nullptr)
        return false;
    
    // Validates the jsonGame and returns it  the json object if the json is valid else returns nullptr.

    return true;

}