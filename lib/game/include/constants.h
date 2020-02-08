#ifndef SOCIAL_GAMING_CONSTANTS_H
#define SOCIAL_GAMING_CONSTANTS_H

#include <string>
#include <vector>
#include <map>
#include "include/nodes.h"
#include "nodes.cpp"
#include "include/json.hpp"

using nlohmann::json;


namespace constants{
    class Constants {
    private:
        //std::list<nodes::Nodes> listOfConstants;
        std::string constantName;
    public:
        void ingestConstants(json &data, std::vector<nodes::Nodes> &listOfConstants);
    };
}

#endif