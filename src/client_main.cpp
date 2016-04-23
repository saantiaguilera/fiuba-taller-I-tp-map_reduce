/*
 * client_main.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <iostream>
#include <string>
#include <stdexcept>

#include "socket/common_SocketException.h"
#include "client/client_Client.h"

int main(int argc, const char *argv[]) {
	//Check that args are available
	if (argc > 2) {
		try {
			std::string host = argv[1];
			std::string port = argv[2];

			//Create a client and run it
			Client client(host, port);
			client.run();

			/**
			 * Because time isnt on my side
			 * im only throwing exceptions for the
			 * sockets, and not some
			 * MalformedDataException or stuff
			 * in case the data they send
			 * contains errors
			 */
		} catch (const SocketException & exception) {
			//Print the exception !
			exception.print();
		}
	}

	return 0;
}

