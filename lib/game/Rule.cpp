#include "include/Rule.h"

using game::Rule;
using game::RuleContainer;
using game::GlobalMessageRule;
using game::Shuffle;
using game::Sort;
using game::Deal;
using game::RuleType;
using game::Timer;
using game::Add;
using game::InputChoice;
using game::InputText;
using game::InputVote;

Rule::Rule(RuleType ruleType, RuleContainer& ruleContainer) : ruleType(ruleType), ruleContainer(ruleContainer) {
    
}

void Rule::setRuleContainer(RuleContainer& ruleContainer) {
    this->ruleContainer = ruleContainer;
}

RuleContainer& Rule::getRuleContainer(){
    return this->ruleContainer;
}

RuleType Rule::getRuleType() const {
    return this->ruleType;
}

//Shuffle
Shuffle::Shuffle(RuleContainer& rule)
{

}
void Shuffle::shuffleList(listName& list)
{

}

RuleContainer& Shuffle::getRule()
{

}
void Shuffle::setRule(RuleContainer& rule)
{

}

//Sort 
void Sort::sortList(listName& list)
{

}
Sort::Sort(RuleContainer& rule)
{

}

RuleContainer& Sort::getRule()
{

}
void Sort::setRule(RuleContainer& rule)
{

}

//Deal
Deal::Deal(RuleContainer& rule)
{

}

RuleContainer& Deal::getRule()
{

}
void Deal::setRule(RuleContainer& rule)
{

}
void Deal::dealList(listName From, listName To, Count count)
{
}

//Timer
Timer::Timer(RuleContainer& rule) 
{

}
RuleContainer& Timer::getRule()
{

}
void Timer::setRule(RuleContainer& rule)
{

}

//Add
Add::Add(RuleContainer& rule) 
{

}
RuleContainer& Add::getRule()
{

}
void Add::setRule(RuleContainer& rule)
{

}

//InputChoice
InputChoice::InputChoice(RuleContainer& rule) 
{}

RuleContainer& InputChoice::getRule()
{}

void InputChoice::setRule(RuleContainer& rule)
{}

//InputText
InputText::InputText(RuleContainer& rule) 
{}

RuleContainer& InputText::getRule()
{}

void InputText::setRule(RuleContainer& rule)
{}

//InputVote
InputVote::InputVote(RuleContainer& rule) 
{}

RuleContainer& InputVote::getRule()
{}

void InputVote::setRule(RuleContainer& rule)
{}
