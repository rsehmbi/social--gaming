#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include <nlohmann/json.hpp>
#include <glog/logging.h>


namespace jsonReader {

    /* 
        The jsonReader class is responsible for reding and validating the json 
        provided by the user for specs and configurations. Right now this consumes
        file path for each file but this can be change to consume json in string 
        format and create a nlohmann::json object.
    */

    class jsonReader {
    public:

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