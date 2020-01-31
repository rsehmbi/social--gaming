/////////////////////////////////////////////////////////////////////////////
//  This code adapts code taken from web-socket-networking chatserver.cpp at
//  https://github.com/nsumner/web-socket-networking into a social platform
//  that supports user specified games
//  This project follows original MIT License. See the LICENSE file
//  for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"
#include "SessionManager.h"

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

//session manager object that manages session messages
SessionManager manager;


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

        //send off to session manager
        manager.processMessages(incoming);
        
        auto outgoing = manager.outboundMessages(clients);

        server.send(outgoing);

        if (errorWhileUpdating) {
            break;
    }

    sleep(1);
    }

  return 0;
}