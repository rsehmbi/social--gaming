#include <iostream>

#include "Client.h"

int main(int argc, char* argv[]){

  if (argc < 3){
    std::cerr << "Usage: \n" 
      << argv[0] << "<ip address> <port>\n"
      << " e.g " << argv[0] << "localhost 44440\n";
    return 1;
  }

  networking::Client client{argv[1], argv[2]};
  bool finish = false;
  auto onTextEntry = [&finish, &client] (std::string text) {
		if (text == "exit" || text == "quit") {
    	finish = true;
  	} else {
    	client.send(text);
  	}
  };

  while (!finish && !client.isDisconnected()) {
  	try {
    	client.update();
		} catch (std::exception& e) {
    	finish = true;
    	std::cout << "Exception from Client update:" << e.what;
  	}

  	auto response = client.receive();
  	if (!response.empty()) {
    	std::cout << "received a new message:" << response;
  	}
  }

	return 0;
}