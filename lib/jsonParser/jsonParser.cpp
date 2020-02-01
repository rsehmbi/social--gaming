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
            LOG(ERROR) << "Could not open specs file. Error: " << strerror(errno);
        }
        return nullptr;
    } catch (const std::exception& e){
        LOG(ERROR) << "Caught exception with message: " << e.what();
    }
    return nullptr;
}

json jsonParser::JsonParser::readGameConfiguration(json jsonSpecs, std::string_view jsonConfigPath){
    try{
        if(jsonConfigPath.empty()){
            json configuration = {};
            jsonSpecs["configuration"] = jsonConfig["configuration"];
            return jsonSpecs;
        } else {
            std::ifstream inStream(std::string(jsonConfigPath).c_str());
            if (inStream.is_open()) {
                json jsonConfig;
                inStream >> jsonConfig;
                jsonSpecs["configuration"] = jsonConfig["configuration"];
                return jsonSpecs;
            } else {
                LOG(ERROR) << "Could not open configs file. Error:" << e.what();
            }
            return nullptr;
        } 
    } catch (const std::exception& e){
         LOG(ERROR) << "Caught exception with message: " << e.what();
    } 
    return nullptr;
}

bool jsonParser::JsonParser::validateGameJson(const json& jsonGame){
    if (jsonGame == nullptr)
        return false;

    // Very basic case is if the game doesn't have configurations or rules.
    if (!jsonGame.contains["configuarations"] || !jsonGame.contains["rules"])
        return false;

    if (jsonGame["Configurations"].contains["setup"]){
        if (!validateConfigurationSetups(jsonGame["Configurations"]["setup"])){
            return false;
        }
    }
    
    // Need to add more cases here.

    return true;

}

bool jsonParser::JsonParser::validateConfigurationSetups(const json& setups){
    if (setups.is_null() || !setups.is_object()){
        return false;

        std::unordered_set <std::string> possible_kinds = 
            {"integer", "string", "boolean", "question-answer", "multiple-choice"};
        for (const auto& setups : setup){
            if (setup.is_object()){
                if (setup.contains("kind") && !setup["kind"].is_string()){
                    return false;
                }
                
                if (setup.contains("prompt") && !setup["prompt"].is_string()){
                    return false;
                }

                if ( !possible_kinds.contains(setup["kind"] ){
                    return false;
                }
            }
        }
    }
}