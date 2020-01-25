#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "Client.h"
#include <unordered_map>

namespace clientManager{
	class ClientManager {
	public:
  // Default constructor for the client manager.
	ClientManager();

	// Destructor from client manager.
	~ClientManager();

	// Send update to the game session when client receives a message. 
	void update(const networking::Client &client, std::string_view response);

	private:
	// Map a player to its client window to send a message to the client.
	// session -> client unique id.
	std::unordered_map<uintptr_t, std::string_view> sessionMap();

	// number of connected clients.
	unsigned int connectedClients;

	// add Connected Clients.
	void incrementConnectedClients();

	// remove Connected Clients.
	void decrementConnectedClients();

	// request to join a session.
	void connectionRequest(const networking::Client &client, std::string_view token)
};
}

#endif