#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
// using game::GlobalMessageRule;
// using game::Shuffle;
// using game::Sort;
// using game::Deal;
using game::RuleType;
// using game::Timer;
// using game::Add;
// using game::InputChoice;
// using game::InputText;
// using game::InputVote;

    std::unordered_map<game::RuleField, std::string> game::ruleFieldToString = {
        {RuleField::rule, "rule"},
        {RuleField::list, "list"},
        {RuleField::element, "element"},
        {RuleField::rules, "rules"},
        {RuleField::until, "until"},
        {RuleField::cases, "cases"},
        {RuleField::target, "target"},
        {RuleField::from, "from"},
        {RuleField::to, "to"},
        {RuleField::count, "count"},
        {RuleField::roles, "roles"},
        {RuleField::value, "value"},
        {RuleField::duration, "duration"},
        {RuleField::mode, "mode"},
        {RuleField::flag, "flag"},
        {RuleField::prompt, "prompt"},
        {RuleField::result, "result"},
        {RuleField::score, "score"},
        {RuleField::ascending, "ascending"},
        {RuleField::timeout, "timeout"},
        {RuleField::choices, "choices"}
    };

    std::unordered_map<std::string, game::RuleField> game::stringToRuleField = {
        {"rule", RuleField::rule},
        {"list", RuleField::list},
        {"element", RuleField::element},
        {"rules", RuleField::rules},
        {"until", RuleField::until},
        {"cases", RuleField::cases},
        {"target", RuleField::target},
        {"from", RuleField::from},
        {"to", RuleField::to},
        {"count", RuleField::count},
        {"roles", RuleField::roles},
        {"value", RuleField::value},
        {"duration", RuleField::duration},
        {"mode", RuleField::mode},
        {"flag", RuleField::flag},
        {"prompt", RuleField::prompt},
        {"result", RuleField::result},
        {"score", RuleField::score},
        {"ascending", RuleField::ascending},
        {"timeout", RuleField::timeout},
        {"choices", RuleField::choices}
    };

Rule::Rule() : m_hasNestedRules(false), m_hasCases(false) {}

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : 
ruleType(ruleType), ruleContainer(ruleContainer), m_hasNestedRules(false), m_hasCases(false) {}

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer, std::vector<Rule>& nestedRules) : 
ruleType(ruleType), ruleContainer(ruleContainer), nestedRules(nestedRules), m_hasNestedRules(true),
m_hasCases(false) { }

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer, std::vector<Rule::Case>& cases) : 
ruleType(ruleType), ruleContainer(ruleContainer), cases(cases), m_hasNestedRules(false),
m_hasCases(true) {}

void Rule::setRuleContainer(RuleContainer& ruleContainer) {
    this->ruleContainer = ruleContainer;
}

RuleType Rule::getRuleType() const {
    return this->ruleType;
}

const RuleContainer& Rule::getRuleContainer() const {
    return this->ruleContainer;
}

const std::vector<Rule>& Rule::getNestedRules() {
    assert(m_hasNestedRules);
    return nestedRules;
}

const std::vector<Rule::Case>& Rule::getCases() {
    assert(m_hasCases);
    return cases;
}

bool Rule::hasNestedRules() {
    return m_hasNestedRules;
}

bool Rule::hasCases() {
    return m_hasCases;
}

std::string Rule::toString() {
    std::string ruleStr = ruleContainer.toString();
    
    if(m_hasNestedRules) {
        ruleStr += "rules: \n{\n";
        for(auto& rule : nestedRules) {
            ruleStr += rule.toString();
        }
        ruleStr += "}\n";
    }
    else if (m_hasCases){
        ruleStr += "cases: \n{\n";
        for(auto& caseItem : cases) {
            ruleStr += caseItem.toString();
        }
        ruleStr += "}\n";
    }
    
    return ruleStr;
}

void game::RuleContainer::add(RuleField item, Value value) {
    ruleInformation[item] = value;
}

const game::Value& game::RuleContainer::get(RuleField item) {
    return ruleInformation[item];
}

std::string game::RuleContainer::toString() {
    std::string str = "";
    for(auto& mapElem : ruleInformation) {
        str += ruleFieldToString[mapElem.first] + ": ";

        if(auto boolValue = std::get_if<bool>(&mapElem.second)) {
            str += std::string(*boolValue ? "true" : "false") + "\n";
        }
        else if (auto intValue = std::get_if<int>(&mapElem.second)) {
            str += std::to_string(*intValue) + "\n";

        }
        else {
            str += std::get<std::string>(mapElem.second) + "\n";
        }
    }
            
    return str;
}

std::string Rule::Case::toString() {
    std::string str = "";
    
    if(auto boolCondition = std::get_if<bool>(&condition)) {
        str += "condition: " + std::string(*boolCondition ? "true" : "false") + "\n";
    } 
    else {
        str += "condition: " + std::get<std::string>(condition) + "\n";
    }

    str += "rules: \n{\n";
    for(auto& rule: rules) {
        str += rule.toString();
    }
    str += "}\n";

    return str;
}

RuleType game::matchRuleType(const nlohmann::json& jsonRuleName) {
    if (jsonRuleName == "global-message") {
        return RuleType::GlobalMessage;
    }
    else if(jsonRuleName == "scores") {
        return RuleType::Scores;
    }
    else if(jsonRuleName == "timer") {
        return RuleType::Timer;
    }
    else if(jsonRuleName == "add") {
        return RuleType::Add;
    }
    else if(jsonRuleName == "foreach") {
        return RuleType::Foreach;
    }
    else if(jsonRuleName == "parallelfor") {
        return RuleType::ParallelFor;
    }
    else if(jsonRuleName == "input-choice") {
        return RuleType::InputChoice;
    }
    else if(jsonRuleName == "discard") {
        return RuleType::Discard;
    }
    else if(jsonRuleName == "when") {
        return RuleType::When;
    }
    else if(jsonRuleName == "extend") {
        return RuleType::Extend;
    }

    return RuleType::Error;
}

bool game::isNestedJsonRule(const nlohmann::json& jsonRule) {
    auto it = std::find_if(jsonRule.items().begin(), jsonRule.items().end(), 
        [] (auto& jsonRule) { 
            return jsonRule.key() == "rules";
        }
    );

    bool isNested = (it != jsonRule.items().end());
    return isNested;
}

bool game::hasCasesInRule(const nlohmann::json& jsonRule) {
    auto it = std::find_if(jsonRule.items().begin(), jsonRule.items().end(), 
        [] (auto& jsonRule) { 
            return jsonRule.key() == "cases";
        }
    );
    
    bool hasCases = (it != jsonRule.items().end());
    return hasCases;
}
