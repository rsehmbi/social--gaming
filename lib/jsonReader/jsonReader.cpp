#include "include/jsonReader.h"

using json = nlohmann::json;


json jsonReader::jsonReader::gameJsonFromFiles(std::string_view specJsonPath, std::string_view configJsonPath){
    json jsonSpecs = readGameSpecFromFile(specJsonPath);
    if (jsonSpecs != nullptr){
        json jsonGame = readGameConfigFromFile(jsonSpecs, configJsonPath);
        if (validateGameJson(jsonGame)){
            return jsonGame;
        } else {
            return nullptr ;
        }
        return jsonGame;
    } else{
        return nullptr;
    }
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
        return nullptr;
    } catch (const std::exception& e){
        LOG(ERROR) << "Caught exception with message: " << e.what();
    }
    return nullptr;
}

json jsonReader::jsonReader::readGameConfigFromFile(json jsonSpecObject, std::string_view jsonConfigPath){
    try{
        if(jsonConfigPath.empty()){
            jsonSpecObject["configuration"] = {};
            return jsonSpecObject;
        } else {
            std::ifstream inStream(std::string(jsonConfigPath).c_str());
            if (inStream.is_open()) {
                json jsonConfig;
                inStream >> jsonConfig;
                jsonSpecObject["configuration"] = jsonConfig["configuration"];
                return jsonSpecObject;
            } else {
                LOG(ERROR) << "Could not open configs file. Error:" << strerror(errno);
            }
            return nullptr;
        } 
    } catch (const std::exception& e){
         LOG(ERROR) << "Caught exception with message: " << e.what();
    } 
    return nullptr;
}



json jsonReader::jsonReader::gameJsonFromJson(std::string_view specJson, std::string_view configJson){
    json jsonSpecObject = readGameSpecFromJson(specJson);
    if (jsonSpecObject != nullptr){
        json jsonGame = readGameConfigFromJson(jsonSpecObject, configJson);
        if (validateGameJson(jsonGame)){
            return jsonGame;
        } else {
            return nullptr ;
        }
    } else{
        return nullptr;
    }
}

nlohmann::json readGameSpecFromJson(std::string_view specJson){
    try{
        json jsonSpecsObject = json(specJson);
        return jsonSpecsObject;
    } catch (const std::exception& e){
        LOG(ERROR) << "Caught exception with message: " << e.what();
    }
    return nullptr;
}

nlohmann::json readGameConfigFromJson(nlohmann::json& jsonSpecObject, std::string_view configJson){
    if(configJson.empty()){
        return jsonSpecObject;
    } else {
        try{
            json jsonConfigObject = json(configJson);
            jsonSpecObject["configuration"] = jsonConfigObject["configuration"];
            return jsonSpecObject;
        } catch (const std::exception& e){
            LOG(ERROR) << "Caught exception with message: " << e.what();
        }
    }
    return jsonSpecObject;
}

bool jsonReader::jsonReader::validateGameJson(const json& jsonGame){
    if (jsonGame == nullptr)
        return false;

    // Very basic case is if the game doesn't have configurations or rules.
    if (!jsonGame.contains["rules"])
        return false;

    if (jsonGame["Configurations"].contains["setup"]){
        if (!validateConfigurationSetups(jsonGame["Configurations"]["setup"])){
            return false;
        }
    }
    
    // Need to add more cases here.

    return true;

}

bool jsonReader::jsonReader::validateConfigurationSetups(const json& setups){
    if (setups.is_null() || !setups.is_object()){
        return true;

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

                if ( possible_kinds.find(setup["kind"]) == possible_kinds.end){
                    return false;
                }
            }
        }
    }
}