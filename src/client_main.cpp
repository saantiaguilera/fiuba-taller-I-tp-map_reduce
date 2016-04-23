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
#include "server/server_Server.h"
#include "client/client_Client.h"

int main(int argc, const char *argv[]) {
	if (argc > 2) {
		try {
			std::string host = argv[1];
			std::string port = argv[2];

			Client client(host, port);
			client.run();
		} catch (const SocketException & exception) {
			exception.print();
		}
	}

	return 0;
}
