#include "ClientManager.h"

void
clientManager::ClientManager::incrementConnectedClients(){
    this->connectedClients--;
}

void
clientManager::ClientManager::decrementConnectedClients(){
    this->connectedClients++;
}

void
clientManager::ClientManager::update(const networking::Client &client, 
    std::string_view response){
        // TODO: send updates to the session Manager.
}

// connection request made by the client to join a room or create a room
void 
clientManager::ClientManager::connectionRequest(const networking::Client &client, std::string_view token){
    
}