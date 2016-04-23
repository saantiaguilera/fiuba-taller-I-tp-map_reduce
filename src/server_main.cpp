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
	if (argc > 1) {
		try {
			std::string port = argv[1];

			Server server(port);
			server.run();
		} catch (const SocketException & exception) {
			exception.print();
		}
	}

	return 0;
}
