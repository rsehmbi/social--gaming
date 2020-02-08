#include "include/jsonReader.h"

using json = nlohmann::json;

json jsonReader::jsonReader::gameJsonFromFiles(std::string_view specJsonPath, std::string_view configJsonPath){
    json jsonSpecs = readGameSpecFromFile(specJsonPath);
    if (jsonSpecs != nullptr){
        json jsonGame = readGameConfigFromFile(jsonSpecs, configJsonPath);
        if (isValidGameJson(jsonGame)){
            return jsonGame;
        }
    }
    return nullptr;
}

json jsonReader::jsonReader::readGameSpecFromFile(std::string_view jsonSpecPath){
    try{
        std::ifstream inStream(std::string(jsonSpecPath).c_str());
        if (inStream.is_open()) {
            json jsonSpecs;
            inStream >> jsonSpecs;
            return jsonSpecs;
        } else {
            LOG(ERROR) << "Could not open specs file. Error: " << strerror(errno);
        }
    } catch (const std::exception& e){
        LOG(ERROR) << "Caught exception with message: " << e.what();
    }
    return nullptr;
}

json jsonReader::jsonReader::readGameConfigFromFile(json& jsonSpecObject, std::string_view jsonConfigPath){
    if(!jsonConfigPath.empty()){
        try{
            std::ifstream inStream(std::string(jsonConfigPath).c_str());
            if (inStream.is_open()) {
                json jsonConfig;
                inStream >> jsonConfig;
                jsonSpecObject["configuration"] = jsonConfig["configuration"];
                return jsonSpecObject;
            } else {
                LOG(ERROR) << "Could not open configs file. Error:" << strerror(errno);
            }
        } catch (const std::exception& e){
         LOG(ERROR) << "Caught exception with message: " << e.what();
        } 
    } 
    
    return jsonSpecObject;
}

bool jsonReader::jsonReader::isValidGameJson(const json& jsonGame){
    if (jsonGame == nullptr)
        return false;

    // Very basic case is if the game doesn't have configurations or rules.
    if (!jsonGame.contains["rules"])
        return false;

    if (jsonGame["Configurations"].contains["setup"]){
        if (!isValidConfigurationSetups(jsonGame["Configurations"]["setup"])){
            return false;
        }
    }
    
    // Need to add more cases here.

    return true;

}

bool jsonReader::jsonReader::isValidConfigurationSetups(const json& setups){
    if (setups.is_null() || !setups.is_object()){
        return true;
    }

    std::unordered_set <std::string> possible_kinds = 
        {"integer", "string", "boolean", "question-answer", "multiple-choice"};
    for (const auto& setup : setups){
        if (setup.is_object()){
            if (setup.contains("kind") && !setup["kind"].is_string()){
                return false;
            }

            if (setup.contains("prompt") && !setup["prompt"].is_string()){
                return false;
            }

            if (possible_kinds.find(setup["kind"].get<std::string>()) == possible_kinds.end()){
                return false;
            }
        }
    }
    return true;
}