/////////////////////////////////////////////////////////////////////////////
//  This code adapts code taken from web-socket-networking chatserver.cpp at
//  https://github.com/nsumner/web-socket-networking into a social platform
//  that supports user specified games
//  This project follows original MIT License. See the LICENSE file
//  for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include "sessionManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>


using networking::Server;
using networking::Connection;
using networking::Message;


std::vector<Connection> clients;
//key value pair mapping connection id to a game session
std::std::unorder_map<uintptr_t, sessionManager*> sessionMap();


void
onConnect(Connection c) {
    std::cout << "New connection found: " << c.id << "\n";
    clients.push_back(c);
}


void
onDisconnect(Connection c) {
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}


struct MessageResult {
  std::string result;
  bool shouldShutdown;
};


MessageResult
processMessages(Server& server, const std::deque<Message>& incoming) {
    std::ostringstream result;
    bool quit = false;
    for (auto& message : incoming) {
    //scan for command in inbound messages
    switch (message.text)
        {
            case "/quit": 
            {
                server.disconnect(message.connection);
                break;
            }
            case "/shutdown":
            {
                std::cout << "Shutting down.\n";
                quit = true;
                break;
            }
            case "/join":
            {
                std::cout << "Joining session...\n";
                //TODO: parse string for session id, then id to sessionMap()
                break;
            }
            case "/create":
            {
                std::cout << "Creating session...\n";
                //TODO: create new session and add id to sessionMap()
                break;
            }
            default:
            {
                result << message.connection.id << "> " << message.text << "\n";
                break;
            }
        }
    }
  return MessageResult{result.str(), quit};
}


std::deque<Message>
buildOutgoing(const std::string& log) {
  std::deque<Message> outgoing;
  for (auto client : clients) {
    outgoing.push_back({client, log});
  }
  return outgoing;
}


std::string
getHTTPMessage(const char* htmlLocation) {
  if (access(htmlLocation, R_OK ) != -1) {
    std::ifstream infile{htmlLocation};
    return std::string{std::istreambuf_iterator<char>(infile),
                       std::istreambuf_iterator<char>()};

  } else {
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
  }
}


int
main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);
    //server that the social gaming platform will be using
  Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};

    //main server loop
    while (true) {
        
        bool errorWhileUpdating = false;

        //send all pending messages out to clients
        try {
            server.update();
        } catch (std::exception& e) {
            std::cerr << "Exception from Server update:\n"
                    << " " << e.what() << "\n\n";
            errorWhileUpdating = true;
        }

        //collect all inbound messages
        auto incoming = server.receive();

        //TO DO:
        //check if any incoming message with create room command
        //sort messages into sessions using session mapping
        //pass session message to sessionManager
        auto [log, shouldQuit] = processMessages(server, incoming);
        auto outgoing = buildOutgoing(log);
        server.send(outgoing);

        if (shouldQuit || errorWhileUpdating) {
            break;
    }

    sleep(1);
    }

  return 0;
}