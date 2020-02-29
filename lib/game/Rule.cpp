#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::GlobalMessageRule;
using game::Shuffle;
using game::Sort;
using game::Deal;

Rule::Rule() {
    // This constructor is required to be explicity declared
    // because it is called by the constructors of subclasses
}

Rule::Rule(RuleContainer& rule) : rule(rule) {}

void Rule::setRule(RuleContainer& rule) {
    this->rule = rule;
}

RuleContainer& Rule::getRule() {
    return this->rule;
}

// GlobalMessageRule class
GlobalMessageRule::GlobalMessageRule(RuleContainer& rule) {
    this->rule = rule;
}

void GlobalMessageRule::setRule(RuleContainer& rule) {
    this->rule = rule;
}

RuleContainer& GlobalMessageRule::getRule() {
    return this->rule;
}

//Shuffle
Shuffle::Shuffle(RuleContainer& rule)
{

}
void Shuffle::shuffleList(listName &list)
{

}

RuleContainer& Shuffle::getRule()
{

}
void Shuffle::setRule(RuleContainer  & rule)
{

}

//Sort 
void Sort::sortList(listName &lis)
{

}
Sort::Sort(RuleContainer& rule)
{

}

RuleContainer& Sort::getRule()
{

}
void Sort::setRule(RuleContainer  & rule)
{

}

//Deal
Deal::Deal(RuleContainer& rule)
{

}

RuleContainer& Deal::getRule()
{

}
void Deal::setRule(RuleContainer  & rule)
{

}
void Deal::dealList(listName From, listName To, Count count)
{

}