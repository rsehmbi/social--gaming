#include <string.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include <SessionManager.h>


#define SESSION_ID_LEN 10

//----------Session Manager Class----------------------
SessionManager::SessionManager() : 
        generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()){
    gamePrompt = "\nThe server supports the following games:\nGame 1\nGame 2\nGame 3\nGame 4\n\n Type /create [game name] to create session.\n";
}

void SessionManager::processMessages(const std::deque<Message>& incoming) {
    outgoing.clear();
    chatLogs.clear();
    for(auto& sessionMsg : msgsForSession){
        sessionMsg.second.clear();
    }
    
    for (auto& message : incoming) {
        CommandType command = commandChecker.checkString(message);

        switch(command) {
            case CommandType::Create: 
                createSession(message.connection.id);
                //console debugging message
                std::cout << "Request for create.\n";
                break;
            case CommandType::Join:
                joinSession(message.connection.id, commandChecker.getArgument());
                //console debugging message
                std::cout << "Request for join.\n";
                break;
            default:
                sortMessage(message);
        }
        
    }
    //Send sorted messages out to sessions. Since server execution is sequential, control is also passed
    //to each session to execute its game turn
    for(auto& pair : sessionMap){
        //first = session ID, second = session object
        //Pass session messages to each session and append (by moving) session output messages
        //to outgoing messages for server to send
        MessageBatch sessionOut = pair.second.processGameTurn(msgsForSession[pair.first]);
        outgoing.insert(outgoing.end(), sessionOut.begin(), sessionOut.end());
    }
  
}

void SessionManager::sortMessage(const Message& message){
    if(connectionSessionMap.find(message.connection.id) == connectionSessionMap.end()){
        std::ostringstream publicStr;
        publicStr << message.connection.id << "> " << message.text << "\n";
        chatLogs["public"] += publicStr.str();
    } else {
        SessionID sid = connectionSessionMap[message.connection.id];
        msgsForSession[sid].push_back(message);
    }
}

void SessionManager::createSession(const ConnectionID& connectionID) {
    //check if connection is already in a session
    if(connectionSessionMap.find(connectionID) != connectionSessionMap.end()){
        outgoing.push_back({connectionID, "You are already in a session. Open a new connection to create another session.\n"});
        return;
    }

    //generate new session id
    SessionID sessionID = generateID();
    
    //create new session and map to session id
    sessionMap.emplace(sessionID, GameSession{ sessionID, connectionID });

    //update records and inform connection of status
    connectionSessionMap[connectionID] = sessionID;
    std::ostringstream outStr;
    outStr << "Session created. Session ID: " << sessionID << "\n";
    outgoing.push_back({connectionID, outStr.str()});

    //tell the session object to add connection to its record
    sessionMap.at(sessionID).connect(connectionID);
    return;
}

void SessionManager::joinSession(const ConnectionID& connectionID, const SessionID& sessionID) {
    
    //check if connection is already in a session
    if(connectionSessionMap.find(connectionID) != connectionSessionMap.end()){
        outgoing.push_back({connectionID,
                            "You are already in a session. Open a new connection to join another session.\n"});
        return;
    }
    //check if sessionID exists
    if(sessionMap.find(sessionID) == sessionMap.end()){
        outgoing.push_back({connectionID, "Invalid session ID\n"});
        return;
    }

    //update records and inform connection of status
    connectionSessionMap[connectionID] = sessionID;
    std::ostringstream outStr;
    outStr << "Connected to session: " << sessionID << "\n";
    outgoing.push_back({connectionID, outStr.str()});
    
    //tell the session object to add connection to its record
    sessionMap.at(sessionID).connect(connectionID);
    return;
}

const std::deque<Message>& SessionManager::outboundMessages(const std::vector<Connection>& clients){
    for(auto& client : clients){
        //public clients
        if(connectionSessionMap.find(client.id) == connectionSessionMap.end()){
            outgoing.push_back({client.id, chatLogs["public"]});
        }
    }
    return outgoing;
}

//generates a random alphanumeric string for session id of specified length
SessionID SessionManager::generateID(){
    std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<int>  distr(0, alphanum.size() - 1);
    SessionID id;
    id.reserve(SESSION_ID_LEN);
    
    //ensure unique session ID
    do {
        for (unsigned i = 0; i < SESSION_ID_LEN; i++) {
            id += alphanum[distr(generator)];
        }
    }
    while(sessionMap.find(id) != sessionMap.end());

    return id;
}

void SessionManager::removeConnection(const ConnectionID& connectionID){
    if(connectionSessionMap.find(connectionID) != connectionSessionMap.end()){
        SessionID sessionid = connectionSessionMap[connectionID];
        sessionMap.at(sessionid).disconnect(connectionID);
    }
    connectionSessionMap.erase(connectionID);
}

std::string SessionManager::getGamesList(){
    return gamePrompt;
}

//----------------CommandChecker Class---------------------


CommandChecker::CommandChecker(){
    commandMap["/create"] = CommandType::Create;
    commandMap["/join"] = CommandType::Join;
}

//checks first word of string and returns CommandType and updates argument accordingly
CommandType CommandChecker::checkString(const Message& message){
    argument = "";
    std::istringstream iss(message.text);
    std::string firstWord;
    iss >> firstWord;
    if (commandMap.find(firstWord) == commandMap.end()){return CommandType::NotACommand;}
    iss >> argument;
    return commandMap[firstWord];
}

std::string CommandChecker::getArgument(){
    return argument;
}
