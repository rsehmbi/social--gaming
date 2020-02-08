#ifndef SOCIAL_GAMING_CONSTANTS_H
#define SOCIAL_GAMING_CONSTANTS_H

#include <string>
#include <list>
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
        void ingestConstants(const json &data);
    };
}

#endif