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
        {RuleField::value, "value"},
        {RuleField::score, "score"},
        {RuleField::ascending, "ascending"},
        {RuleField::to, "to"},
        {RuleField::duration, "duration"},
        {RuleField::mode, "mode"},
    };

    std::unordered_map<std::string, game::RuleField> game::stringToRuleField = {
        {"rule", RuleField::rule},
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
    };

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    hasNestedRules = false;
}

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer, std::vector<Rule>& nestedRules) : 
ruleType(ruleType), ruleContainer(ruleContainer), nestedRules(nestedRules)  {
    hasNestedRules = true;
}

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
    assert(hasNestedRules);
    return nestedRules;
}

std::string Rule::toString() {
    std::string ruleStr = ruleContainer.toString();
    
    if(hasNestedRules) {
        ruleStr += "rules: \n{\n";
        for(auto& rule : nestedRules) {
            ruleStr += rule.toString();
        }
        ruleStr += "}\n";
    }
    
    return ruleStr;
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