#include "include/interpreter.h"
#include "include/json.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <random>       // std::default_random_engine
#include <chrono>
#include "GameSession.h"

using interpreter::Interpreter;
using namespace game;
using namespace std;

Interpreter::Interpreter () {
}

void 
Interpreter::setCurrentGameSession(GameSessionInterface* session, RunningGameState* gameState,
                                   const Constants* constants, const GameRules* rules){
    mSession = session;
    gameState = gameState;
    rules = rules;
    constants = constants;
}

//void interpreter::Interpreter::processRules(json gameRules, json gameData){
//    json ruleBlock = getNextRuleBlock(gameRules);
//    if(hasNestedRules(ruleBlock)){
//        processRules(ruleBlock, gameData);
//    }
//    //calls processor to process rule block
//}

std::shared_ptr<Variable> processToList(std::string domainLanguage){
    //TODO: implement the evaluation of command such as
    // !players.elements.weapon.contains(weapon.name) To a vector.
    // DomainNameTranslator's job?
    std::shared_ptr<Variable> listVariablePtr = std::make_shared<Variable>();
    listVariablePtr->varType = VariableType::ListType;

    return listVariablePtr;
}

VariablePtr getVariablePtrFromMap(std::unordered_map<std::string, VariablePtr> mapVariables, std::string name){
    // VariablePtr element = std::find(mapVariables.begin, mapVariables.end, name);
    std::unordered_map<std::string, VariablePtr>::const_iterator found = mapVariables.find(name);

    if(found != mapVariables.end()){
        return found->second;
    }else{
        for(auto var : mapVariables){
            VariablePtr foundVar = getVariablePtrFromMap(var.second->mapVar, name);
            if(foundVar != nullptr){
                return foundVar;
            }
        }
    }
    return nullptr;
}

std::string converseListToString(std::shared_ptr<Variable> list){
    //TODO:implementation
    return "";
}

void interpreter::Interpreter::processRuleChoice(Rule &rule){
    RuleType ruleType = rule.getRuleType();
    switch(ruleType){
        case RuleType::Add:
            executeAdd(rule);
            break;
        case RuleType::Deal:
            executeDeal(rule);
            break;
        case RuleType::Discard:
            executeDiscard(rule);
            break;
        case RuleType::Extend:
            executeExtend(rule);
            break;
        case RuleType::Foreach:
            executeForEach(rule);
            break;
        case RuleType::GlobalMessage:
            executeGlobalMessage(rule);
            break;
        case RuleType::Inparallel:
            executeInparallel(rule);
            break;
        case RuleType::InputChoice:
            executeInputChoice(rule);
            break;
        case RuleType::InputText:
            executeInputText(rule);
            break;
        case RuleType::InputVote:
            executeInputVote(rule);
            break;
        case RuleType::Message:
            executeMessage(rule);
            break;
        case RuleType::Loop:
            executeLoop(rule);
            break;
        case RuleType::ParallelFor:
            executeParallelFor(rule);
            break;
        case RuleType::Reverse:
            executeReverse(rule);
            break;
        case RuleType::Scores:
            executeScores(rule);
            break;
        case RuleType::Shuffle:
            executeShuffle(rule);
            break;
        case RuleType::Sort:
            executeSort(rule);
            break;
        case RuleType::Switch:
            executeSwitch(rule);
            break;
        case RuleType::Timer:
            executeTimer(rule);
            break;
        case RuleType::When:
            executeWhen(rule);
            break;
        break;     
    }
}


void interpreter::Interpreter::executeExtend(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string targetList = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> targetListPtr =this->gameState->variables->getVariable(targetList);
    //must be a list type
    if(targetListPtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeExtend error, type mismatch; not ListType" <<std::endl;
    }
    std::string listCommands = std::get<std::string>(container.ruleInformation.at(RuleField::list));
    std::shared_ptr<Variable> sourceVariablePtr = processToList(listCommands);

    targetListPtr->listVar.insert(targetListPtr->listVar.end(),
                    sourceVariablePtr->listVar.begin(), sourceVariablePtr->listVar.end());
}

void interpreter::Interpreter::executeReverse(Rule &rule){
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));
    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    //must be a list type
    if(listVariablePtr->varType != VariableType::ListType){
        std::cout << std::endl << "executeReverse error, type mismatch; not ListType" <<std::endl;
    }
    std::reverse(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end());
}

void interpreter::Interpreter::executeShuffle(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));

    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    try {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end(),std::default_random_engine(seed));
    }
    catch (exception &e)
    {
        LOG(INFO) << "Shuffle failed in Interpreter" << e.what();
    }
}

void interpreter::Interpreter::executeSort(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string listName = std::get<std::string>(container.ruleInformation.at(RuleField::target));

    std::shared_ptr<Variable> listVariablePtr = this->gameState->variables->getVariable(listName);
    try {
        std::sort(listVariablePtr->listVar.begin(), listVariablePtr->listVar.end());
    }
    catch (exception &e)
    {
        LOG(INFO) << "Sort failed in Interpreter" << e.what();
    }
}

void interpreter::Interpreter::executeDeal(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string From = std::get<std::string>(container.ruleInformation.at(RuleField::from));
    std::string To = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    int Count =  std::get<int >(container.ruleInformation.at(RuleField::count));
    int numberOfElements = 0;
    std::shared_ptr<Variable> fromVariablePtr = processToList(From);
    std::shared_ptr<Variable> toVariablePtr = processToList(To);

    try {
        for (int iterator = 0; iterator < numberOfElements;iterator++ )
        {
            toVariablePtr->listVar.push_back(fromVariablePtr->listVar.front());
            fromVariablePtr->listVar.erase(fromVariablePtr->listVar.begin());
        }
    }
    catch (exception &e)
    {
        LOG(INFO) << "Deal failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeForEach(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    //RuleField Values
    std::string list = std::get<std::string>(container.ruleInformation.at(RuleField::list));
    std::string element = std::get<std::string>(container.ruleInformation.at(RuleField::element));
    // std::string rules = std::get<std::string>(container.ruleInformation.at(RuleField::rules));
    //TODO: fix using domainnametranslator
    VariablePtr listPtr = processToList(list); // = parseInstruction(list, gameState) 

    //Insert new element into list
    std::pair<std::string, VariablePtr> insertion(element, VariablePtr{});
    listPtr->mapVar.insert(insertion);

    //Process nested rules
    if(!rule.hasNestedRules()){
        LOG(INFO) << "executeForEach error, has no nested rules" << std::endl;
    }   
    std::vector<game::Rule> nestedRuleList = rule.getNestedRules();
    for(auto aRule : nestedRuleList){
        processRuleChoice(aRule);
    }
    
}

void interpreter::Interpreter::executeLoop(Rule &rule) {

}

void interpreter::Interpreter::executeInparallel(Rule &rule) {

}

void interpreter::Interpreter::executeParallelFor(Rule &rule) {

}

void interpreter::Interpreter::executeSwitch(Rule &rule) {

}

void interpreter::Interpreter::executeWhen(Rule &rule) {

}

void interpreter::Interpreter::executeDiscard(Rule &rule) { 
    const RuleContainer& container = rule.getRuleContainer();
    std::string from = std::get<std::string>(container.ruleInformation.at(RuleField::from));
    int count =  std::get<int>(container.ruleInformation.at(RuleField::count));
    //Count will not work as intended if count datatype is not Int, such as winner.size, because DomainNameTranslator doesn't have the function to parse

    std::shared_ptr<Variable> fromPtr = processToList(from);

    if(fromPtr->varType != VariableType::ListType){
        LOG(INFO) << "executeDiscard error, type mismatch; not ListType" <<std::endl;
    }

    try{
        for(int i = 0; i < count; ++i){
            fromPtr->listVar.erase(fromPtr->listVar.begin());
        }
    }catch(exception &e){
        LOG(INFO) << "Discard failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeAdd(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string to = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    int value =  std::get<int>(container.ruleInformation.at(RuleField::value)); // only works with Int

    std::shared_ptr<Variable> toPtr = this->gameState->variables->getVariable(to);

    if(toPtr->varType != VariableType::NumberType){
        LOG(INFO) <<  "executeAdd error, type mismatch; not NumberType" <<std::endl;
    }

    try{
        toPtr->intVar = toPtr->intVar + value;
    }catch(exception &e){
        LOG(INFO) << "Add failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeTimer(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    TimerLength duration = std::get<TimerLength>(container.ruleInformation.at(RuleField::duration));
    Mode mode = std::get<Mode>(container.ruleInformation.at(RuleField::mode));

    if(!rule.hasNestedRules()){
        LOG(INFO) << "executeTimer error, has no nested rules" << std::endl;
    }
    std::vector<game::Rule> nestedRuleList = rule.getNestedRules();

    //init timer
    std::clock_t start;
    start = std::clock();
    if(mode == "at most"){
        for(auto aRule : nestedRuleList){
            if((std::clock() - start) < duration){
                processRuleChoice(aRule);
            }else{
                break;
            }          
        }
    }else if(mode == "exact"){
        while((std::clock() - start) < duration){};
        for(auto aRule : nestedRuleList){
            processRuleChoice(aRule);
        }
    }else if(mode == "track"){
        //TODO: track mode
    }else{
        LOG(INFO) << "executeTimer error, mode not recognized" << std::endl;
    }

}

void interpreter::Interpreter::processRules(Rule &rule) {

}

void interpreter::Interpreter::executeInputChoice(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    
    std::string to = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    std::string prompt = std::get<std::string>(container.ruleInformation.at(RuleField::prompt));
    std::string choices = std::get<std::string>(container.ruleInformation.at(RuleField::choices));
    std::string result = std::get<std::string>(container.ruleInformation.at(RuleField::result));
    std::shared_ptr<Variable> choicesPtr = processToList(choices);
    if(choicesPtr->varType != VariableType::ListType){
            LOG(INFO) << "executeInputChoices error, type mismatch; playerVar not ListType" <<std::endl;
        }
     
    try{        
        std::vector<UserIdType> toListId; //use domainNameTranslator to find UserIdtype of reciepients
        std::vector<user::User> userList = dynamic_cast<GameSession*>(mSession)->getPlayers();   
        std::string choicesString = converseListToString(choicesPtr);

        //Send global message
        for(auto user : userList){
            if(std::find(toListId.begin(), toListId.end(), user.getId()) != toListId.end()){
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)prompt));
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)choicesString));
            }
        }

        //Insert result variable into user for input
        std::string userType;
        if(to == "player"){
            userType = "players";
        }else if(to == "audience"){
            userType = "audiences";
        }else{
             LOG(INFO) << "executeInputChoices error, to user not recognized" <<std::endl;
        }
        std::unordered_map<std::string, VariablePtr> userMap = gameState->variables->getVariable(userType)->mapVar;
        std::string userId; //use domainNameTranslator to find userId of reciepients in GameSession
        userMap.find(userId)->second->mapVar.insert(std::pair<std::string, VariablePtr> (result, VariablePtr{}));
    }catch(exception &e){
        LOG(INFO) << "InputChoice failed in Interpreter while processing a list" << e.what();  
    }
}

void interpreter::Interpreter::executeInputVote(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    
    std::string to = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    std::string prompt = std::get<std::string>(container.ruleInformation.at(RuleField::prompt));
    std::string choices = std::get<std::string>(container.ruleInformation.at(RuleField::choices));
    std::string result = std::get<std::string>(container.ruleInformation.at(RuleField::result));
    std::shared_ptr<Variable> choicesPtr = processToList(choices);
    if(choicesPtr->varType != VariableType::ListType){
            LOG(INFO) << "executeInputVote error, type mismatch; playerVar not ListType" <<std::endl;
        }
     
    try{        
        std::vector<UserIdType> toListId; //use domainNameTranslator to find UserIdtype of reciepients
        std::vector<user::User> userList = dynamic_cast<GameSession*>(mSession)->getPlayers();   
        std::string choicesString = converseListToString(choicesPtr);

        //Send global message
        for(auto user : userList){
            if(std::find(toListId.begin(), toListId.end(), user.getId()) != toListId.end()){
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)prompt));
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)choicesString));
            }
        }

        //Insert result variable into user for input
        std::string userType;
        if(to == "player"){
            userType = "players";
        }else if(to == "audience"){
            userType = "audiences";
        }else{
             LOG(INFO) << "executeInputVote error, to user not recognized" <<std::endl;
        }
        std::unordered_map<std::string, VariablePtr> userMap = gameState->variables->getVariable(userType)->mapVar;
        std::string userId; //use domainNameTranslator to find userId of reciepients in GameSession
        userMap.find(userId)->second->mapVar.insert(std::pair<std::string, VariablePtr> (result, VariablePtr{}));
    }catch(exception &e){
        LOG(INFO) << "InputVote failed in Interpreter while processing a list" << e.what();  
    }
}

void interpreter::Interpreter::executeInputText(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    
    std::string to = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    std::string prompt = std::get<std::string>(container.ruleInformation.at(RuleField::prompt));
    std::string result = std::get<std::string>(container.ruleInformation.at(RuleField::result));
     
    try{        
        std::vector<UserIdType> toListId; //use domainNameTranslator to find UserIdtype of reciepients
        std::vector<user::User> userList = dynamic_cast<GameSession*>(mSession)->getPlayers();   

        //Send global message
        for(auto user : userList){
            if(std::find(toListId.begin(), toListId.end(), user.getId()) != toListId.end()){
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)prompt));
            }
        }

        //Insert result variable into user for input
        std::string userType;
        if(to == "player"){
            userType = "players";
        }else if(to == "audience"){
            userType = "audiences";
        }else{
             LOG(INFO) << "executeInputText error, to user not recognized" <<std::endl;
        }
        std::unordered_map<std::string, VariablePtr> userMap = gameState->variables->getVariable(userType)->mapVar;
        std::string userId; //use domainNameTranslator to find userId of reciepients in GameSession
        userMap.find(userId)->second->mapVar.insert(std::pair<std::string, VariablePtr> (result, VariablePtr{}));
    }catch(exception &e){
        LOG(INFO) << "InpuText failed in Interpreter while processing a list" << e.what();  
    }
}

void interpreter::Interpreter::executeMessage(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string to = std::get<std::string>(container.ruleInformation.at(RuleField::to));
    std::string value =  std::get<std::string>(container.ruleInformation.at(RuleField::value));

    std::vector<UserIdType> toListId; //use domainNameTranslator to find UserIdtype of reciepients
    std::vector<user::User> userList = dynamic_cast<GameSession*>(mSession)->getPlayers();
    try{
        for(auto user : userList){
            if(std::find(toListId.begin(), toListId.end(), user.getId()) != toListId.end()){
                this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)value));
            }
        }
    }catch(exception &e){
        LOG(INFO) << "Global Message failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeGlobalMessage(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    std::string value =  std::get<std::string>(container.ruleInformation.at(RuleField::value));
    
    std::vector<user::User> userList = dynamic_cast<GameSession*>(mSession)->getPlayers();
    
    try{
        for(auto user : userList){
            this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(user.getConnectionID(), (MessageText)value));
        }
    }catch(exception &e){
        LOG(INFO) << "Global Message failed in Interpreter while processing a list" << e.what();
    }
}

void interpreter::Interpreter::executeScores(Rule &rule) {
    const RuleContainer& container = rule.getRuleContainer();
    //RuleField Values
    std::string score = std::get<std::string>(container.ruleInformation.at(RuleField::score));
    bool ascending =  std::get<bool>(container.ruleInformation.at(RuleField::ascending));
    
    std::vector<user::User> playerList = dynamic_cast<GameSession*>(mSession)->getPlayers();
    game::VariablePtr playerVar = gameState->variables->getVariable("players");
    if(playerVar->varType != VariableType::ListType){
        LOG(INFO) << "executeScores error, type mismatch; playerVar not ListType" <<std::endl;
    }
    std::unordered_map<std::string, VariablePtr> playerMap = playerVar->mapVar;
    std::vector<std::pair<std::string, int>> sortScore;
    std::string message = "Score List\n";

    try{
        //Insert scores into sort map
        for(auto player : playerMap){
            VariablePtr scorePtr = getVariablePtrFromMap(player.second->mapVar, score);
            if(scorePtr->varType != VariableType::NumberType){
                LOG(INFO) << "executeScores error, type mismatch; scorePtr not NumberType" << std::endl;
            }   

            sortScore.emplace_back(std::make_pair(player.first, scorePtr->intVar));
        }

        //Sort scores based on ascending value
        if(ascending){
            std::sort(sortScore.begin(), sortScore.end(), [](std::pair<std::string, int> first, std::pair<std::string, int> second) -> bool{
                return second > first;
            });
        }else{
            std::sort(sortScore.begin(), sortScore.end(), [](std::pair<std::string, int> first, std::pair<std::string, int> second) -> bool{
                return second < first;
            });
        }

        //Create message content
        for(auto element : sortScore){
            message += "Player: " + element.first;
            message += "\tScore: " + element.second;
            message += "\n";
        }

        //Send global message
        for(user::User player : playerList){
            this->gameState->messageMap.insert(std::make_pair<UserIdType, MessageText>(player.getConnectionID(), (MessageText)message));
        }
    }catch(exception &e){
        LOG(INFO) << "Score failed in Interpreter while processing a list" << e.what();  
    }
}


