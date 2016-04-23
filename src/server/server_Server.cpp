/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "../socket/common_Socket.h"
#include "stdexcept"
#include "server_Server.h"

Server::Server(std::string &port) {
	socket = new Socket();
	socket->bind(port);

	//TODO Create a parser and serializer base class if time is on my side
	parser = new DayParser();
	serializer = new DaySerializer();

	if (socket->connectivityState != CONNECTIVITY_OK)
		throw std::runtime_error("Cant connect!! (ﾉಥ益ಥ）ﾉ﻿ ┻━┻"); //refactor this
}

Server::~Server() {
	delete socket;
	delete parser;
	delete serializer;
}

void Server::run() {

}
