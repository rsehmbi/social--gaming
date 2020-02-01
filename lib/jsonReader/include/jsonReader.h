#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <glog/logging>


namespace jsonReader {

    /* 
        The jsonReader class is responsible for reding and validating the json 
        provided by the user for specs and configurations. Right now this consumes
        file path for each file but this can be change to consume json in string 
        format and create a nlohmann::json object.
    */

    class jsonReader {
    public:

        nlohmann::json createGame(std::string_view specJsonPath, std::string_view configJsonPath);

    private:
        nlohmann::json readGameSpecification(std::string_view path);

        nlohmann::json readGameConfiguration(nlohmann::json jsonGame, std::string_view path);

        bool validateGameJson(const nlohmann::json& jsonGame);

        bool validateConfigurationSetups(const json& setups)
    
    };
}

#endif