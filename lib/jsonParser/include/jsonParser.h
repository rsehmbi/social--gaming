#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace jsonParser {

    // The Interpreter class is responsible for interpreting
    // game rules that are specified in a JSON file
    class JsonParser {
    public:

        nlohmann::json createGame(std::string_view specJsonPath, std::string_view configJsonPath);

    private:
        nlohmann::json readGameSpecification(std::string_view path);

        nlohmann::json readGameConfiguration(nlohmann::json jsonGame, std::string_view path);
    };
}

#endif