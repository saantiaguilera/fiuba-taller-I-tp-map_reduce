/*
 * client_Client.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <string>
#include "../socket/common_Socket.h"
#include "stdexcept"
#include "../socket/common_SocketException.h"
#include "client_Client.h"
#include "iostream"

/**
 * @Public
 * @Constructor
 */
Client::Client(std::string &host, std::string &port) {
	//Parser and serializer it will use
	parser = new MapperFileParser();
	serializer = new MapperSerializer();

	//Init the socket and connect to the given host:port
	socket = new Socket();
	socket->connect(port, host);

	//Throw exception on error
	/**
	 * This exceptions should be thrown from inside socket
	 * But since I dont have enough time (other subjects)
	 * I couldnt change the whole socket.c class and Im
	 * throwing only were I found most critical situations
	 * the exceptions (like bind or send)
	 */
	if (socket->connectivityState != CONNECTIVITY_OK)
		throw SocketException(
				"Client failed to connect to " + host + ":" + port);
}

/**
 * @Public
 * @Destructor
 */
Client::~Client() {
	delete socket;
	delete parser;
	delete serializer;
}

/**
 * @Public
 * @note This method runs the whole
 * client operation
 * 1. Reads the whole standard input by lines
 * and creates for each a Model, which will be
 * mapped and send through the socket to the server
 */
void Client::run() {
	std::string line;

	//As long as there are lines...
	while (std::getline(std::cin, line)) {
		if (!line.empty()) {
			//Parse the line and serialize it in the
			//Map format
			MapperModel *mapperModel = parser->parse(line);
			std::string mappedData = serializer->serialize(*mapperModel);
			delete mapperModel;

			//Send the mapped data, throw exception on error
			if (socket->send(mappedData) != REQUEST_RECEIVING_DATA)
				throw SocketException(
						"Client failed to send data: " + mappedData);
		}
	}

	//On finish, for protocol send an "End\n"
	std::string end("End\n");
	if (socket->send(end) != REQUEST_RECEIVING_DATA)
		throw SocketException(
				"Client failed to send data: " + end);
}
