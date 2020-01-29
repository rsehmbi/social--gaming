#include "SessionManager.h"
#include <string.h>
#include <sstream>
#include <iostream>

#define SESSION_ID_LEN 10

//parses input by space and returns second token
std::string parseSecondWord(const std::string& input){
    std::istringstream iss(input);
    std::string out;
    iss >> out;
    iss >> out;
    return out;
}

//Definition of Session Manager class
SessionManager::SessionManager() {  //constructor
    //connection ids are mapped to session
    //if sessionMap() does not contain connection id, it is in public chat (not in any session)
    std::unordered_map<uintptr_t, std::string> connectionMap;

    //a set of sessions objects
    std::unordered_map<std::string, Session> sessionMap;
    
    //outbound msgs
    std::deque<Message> outgoing;

    //initialize a random generator
    std::random_device                  rand_dev;//seed for mt19937
    std::mt19937                        generator(rand_dev());
}

void SessionManager::processMessages(const std::deque<Message>& incoming, const std::vector<Connection>& clients) {
    
    for (auto& message : incoming) {
        //create session request
        if (message.text.find("/create") != std::string::npos) {
            createSession(message.connection.id);
            std::cout << "Request for create.\n";

        //join session request
        } else if (message.text.find("/join")) {
            //parse string for id number
            std::string sessionID = parseSecondWord(message.text);
            joinSession(message.connection.id, sessionID);
            std::cout << "Request for join.\n";
        
        //close session request
        } else if (message.text.find("/close")){
            
        } else if (message.text.find("/chowner")) {

        } else {
            //TODO: perform sort by connectionMap and deliver to sorted messages to session by sessionMap
            //if not in connectionMap, append to public chat log
            // result << message.connection.id << "> " << message.text << "\n";
        }
    }
  
  
}

void SessionManager::createSession(const uintptr_t& connectionID) {
    //check if connection is already in a session
    if(connectionMap.find(connectionID) != connectionMap.end()){
        outgoing.push_back({connectionID, "You are already in a session. Open a new connection to create another session.\n"});
        return;
    }

    //generate new session id
    std::string sessionID = generateID();
    //ensure unique session ID
    while(sessionMap.find(sessionID) != sessionMap.end()){
        sessionID = generateID();
    }
    //create new session and map to session id
    sessionMap[sessionID] = Session{sessionID};
    connectionMap[connectionID] = sessionID;
    std::ostringstream oss;
    oss << "Session created. Session ID: " << sessionID << "\n";
    outgoing.push_back({connectionID, oss.str()});
    return;
}

void SessionManager::joinSession(const uintptr_t& connectionID, const std::string& sessionID) {
    
    //check if connection is already in a session
    if(connectionMap.find(connectionID) != connectionMap.end()){
        outgoing.push_back({connectionID,
                            "You are already in a session. Open a new connection to join another session.\n"});
        return;
    }

    //check if sessionID exists
    if(sessionMap.find(sessionID) == sessionMap.end()){
        outgoing.push_back({connectionID, "Invalid session ID\n"});
        return;
    }

    connectionMap[connectionID] = sessionID;
    std::ostringstream oss;
    oss << "Connected to session: " << sessionID << "\n";
    outgoing.push_back({connectionID, oss.str()});
    return;
}

std::deque<Message> SessionManager::outboundMessages(){

}

//generates a random alphanumeric string for session id of specified length
std::string SessionManager::generateID(){
    std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<int>  distr(0, alphanum.size() - 1);
    std::string out;
    for (unsigned i = 0; i < SESSION_ID_LEN; i++) {
        out += alphanum[distr(generator)];
    }
    return out;
}

// void SessionManager::addOwner(const Connection& ownerC)
// {
    
// }

// void SessionManager::addPlayer(const Connection& playerC)
// {

// }

// void SessionManager::broadCast(const std::string& s)
// {

// }


// void SessionManager::sendMsg(const unsigned int player, const std::string& s)
// {

// }

// void SessionManager::receiveMsg(std::deque<Message>& messages)
// {

// }
