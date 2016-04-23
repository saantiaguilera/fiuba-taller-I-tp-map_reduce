/*
 * client_Client.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "../socket/common_Socket.h"
#include "stdexcept"
#include "client_Client.h"
#include "iostream"

Client::Client(std::string &host, std::string &port) {
	socket = new Socket();
	socket->connect(port, host);

	//TODO Create a parser and serializer base class if time is on my side
	parser = new MapperFileParser();
	serializer = new MapperSerializer();

	if (socket->connectivityState != CONNECTIVITY_OK)
		throw std::runtime_error("Cant connect!! (ﾉಥ益ಥ）ﾉ﻿ ┻━┻"); //refactor this

	std::cout << "Finished initializing" << std::endl;
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

		std::cout << "Model is:: " << mapperModel->first << " " << mapperModel->second.first << " " << mapperModel->second.second << std::endl;

		std::string mappedData = serializer->serialize(*mapperModel);

		if (socket->send(mappedData) != REQUEST_RECEIVING_DATA)
			throw std::runtime_error("Cant send!! (ﾉಥ益ಥ）ﾉ﻿ ┻━┻"); //refactor this
		else std::cout << "Data sent." << std::endl;

		delete mapperModel;
	}

	std::cout << "Finished reading" << std::endl;

	std::string end("End\n");
	socket->send(end);
}
