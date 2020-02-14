#ifndef JSONREADER_H
#define JSONREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include <glog/logging.h>
#include "json.hpp"


namespace jsonReader {

    /* 
        The jsonReader class is responsible for reding and validating the json 
        provided by the user for specs and configurations. Right now this consumes
        file path for each file but this can be change to consume json in string 
        format and create a nlohmann::json object.
    */

    class jsonReader {
    public:

        // static constant keys used to validate data from json.
        static inline const std::string str_configurations = "configuration";
        static inline const std::string str_rules = "rules";
        static inline const std::string str_setup = "setup";
        static inline const std::string str_kind = "kind";
        static inline const std::string str_prompt = "prompt";

        nlohmann::json gameJsonFromFiles(std::string_view specJsonPath, std::string_view configJsonPath);

        nlohmann::json gameJsonFromJson(std::string_view specJson, std::string_view configJson);

    private:
        
        nlohmann::json readGameSpecFromFile(std::string_view path);

        nlohmann::json readGameConfigFromFile(nlohmann::json& jsonSpecObject, std::string_view path);

        bool isValidGameJson(const nlohmann::json& jsonGame);

        bool isValidConfigurationSetups(const nlohmann::json& setups);
    };
}

#endif