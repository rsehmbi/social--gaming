#include "JsonReader.h"

using json = nlohmann::json;


json jsonReader::jsonReader::gameJsonFromFiles(std::string_view specJsonPath, std::string_view configJsonPath){
    LOG(INFO) << "About to read json files with name: " << specJsonPath << ", " << configJsonPath;
    json jsonSpecs = readGameSpecFromFile(specJsonPath);
    if (jsonSpecs != nullptr){
        json jsonGame = readGameConfigFromFile(jsonSpecs, configJsonPath);
        if (isValidGameJson(jsonGame)){
            return jsonGame;
        }
    }
    LOG(ERROR) << "Failed reading/validating game";
    return nullptr;
}

json jsonReader::jsonReader::readGameSpecFromFile(std::string_view jsonSpecPath){
    try{
        LOG(INFO) << "Reading json Specifications from file: " << jsonSpecPath;
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
            LOG(INFO) << "Reading json Configurations from file: " << jsonConfigPath;
            std::ifstream inStream(std::string(jsonConfigPath).c_str());
            if (inStream.is_open()) {
                json jsonConfig;
                inStream >> jsonConfig;
                jsonSpecObject[str_configurations] = jsonConfig[str_configurations];
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
    LOG(INFO) << "Validating json game";

    if (jsonGame == nullptr)
        return false;

    // Very basic case is if the game doesn't have configurations or rules.
    if (!jsonGame.contains(str_rules) || !jsonGame.contains(str_configurations))
        return false;

    if (jsonGame[str_configurations].contains(str_setup)){
        if (!isValidConfigurationSetups(jsonGame[str_configurations][str_setup])){
            return false;
        }
    }
    
    // Need to add more cases here.

    LOG(INFO) << "Game Validated";
    return true;

}

bool jsonReader::jsonReader::isValidConfigurationSetups(const json& setups){
    LOG(INFO) << "Validating json configuration setups";
    
    if (setups.is_null() || !setups.is_object()){
        return true;
    }

    std::unordered_set <std::string> possible_kinds = 
        {"integer", "string", "boolean", "question-answer", "multiple-choice"};
    for (const auto& setup : setups){
        if (setup.is_object()){
            if (setup.contains(str_kind) && !setup[str_kind].is_string()){
                return false;
            }

            if (setup.contains(str_prompt) && !setup[str_prompt].is_string()){
                return false;
            }

            if (possible_kinds.find(setup[str_kind].get<std::string>()) == possible_kinds.end()){
                return false;
            }
        }
    }
    return true;
}