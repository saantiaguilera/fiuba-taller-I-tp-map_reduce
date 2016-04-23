/*
 * server_main.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <iostream>
#include <string>
#include <stdexcept>

#include "socket/common_SocketException.h"
#include "server/server_Server.h"

int main(int argc, const char *argv[]) {
	//Check that arguments are available
	if (argc > 1) {
		try {
			std::string port = argv[1];

			//Create a server and run it
			Server server(port);
			server.run();

			/**
			 * Because time isnt on my side
			 * im only throwing exceptions for the
			 * sockets, and not some
			 * MalformedDataException or stuff
			 * in case the data they send
			 * contains errors
			 */
		} catch (const SocketException & exception) {
			//If a socket throws an excep print it
			exception.print();
		}
	}

	return 0;
}
