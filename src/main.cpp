//============================================================================
// Name        : client_main.cpp
// Author      : Santi Aguilera
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <string>
#include <stdexcept>

#include "server/server_Server.h"
#include "client/client_Client.h"

int main() {
	std::string port("8080");
	std::string host("127.0.0.1");

/*
	Server server(port);
	server.run();
*/


	Client client(host, port);
	client.run();


	return 0;
}
