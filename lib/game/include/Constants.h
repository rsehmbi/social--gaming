#ifndef SOCIAL_GAMING_CONSTANTS_H
#define SOCIAL_GAMING_CONSTANTS_H

#include <string>
#include <vector>
#include <map>
#include "nodes.h"
#include "json.hpp"

using nlohmann::json;


namespace game{
    class Constants {
    private:
        //std::list<nodes::Nodes> listOfConstants;
        std::string constantName;
    public:
        //Converts Constants from Json to C++ vector
        void ingestConstants(json &data, std::vector<nodes::Nodes> &listOfConstants);
    };
}

#endif