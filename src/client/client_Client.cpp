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

Client::Client(std::string &host, std::string &port) {
	parser = new MapperFileParser();
	serializer = new MapperSerializer();

	socket = new Socket();
	socket->connect(port, host);

	if (socket->connectivityState != CONNECTIVITY_OK)
		throw SocketException(
				"Client failed to connect to " + host + ":" + port);
}

Client::~Client() {
	delete socket;
	delete parser;
	delete serializer;
}

void Client::run() {
	std::string line;

	while (std::getline(std::cin, line)) {
		MapperModel *mapperModel = parser->parse(line);
		std::string mappedData = serializer->serialize(*mapperModel);
		delete mapperModel;

		if (socket->send(mappedData) != REQUEST_RECEIVING_DATA)
			throw SocketException(
					"Client failed to send data: " + mappedData);
	}

	std::string end("End\n");
	if (socket->send(end) != REQUEST_RECEIVING_DATA)
		throw SocketException(
				"Client failed to send data: " + end);
}
