/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "server_Server.h"

Server::Server(std::string &port) {
	socket = new Socket();
	socket->bind(port);

	clientList = new ConcurrentList<Socket*>();

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
	delete clientList; //TODO Care of the leak of his elements
}

void Server::run() {
	/**
	 * DONE - 1. Spawn a worker that listens and accepts sockets. Save sockets in a list.
	 * 2. Each spawned worker should start recv data, for each model they parse, they append it to a
	 * thread safe list of day models
	 * 3. When server finds Q, interrupts the socket manager worker (find a workaround, interrupt is
	 * bad smell). Use a boolean shared element !!!  Goto 9. and return back in a while
	 * 4. Iterate through the socket list joining them (so we start 5. knowing all data is filled)
	 * 5. Iterate through the model list and go removing by id (like. first remove all day:1 and append it
	 * to another list). For each day spawn a worker with his according list. Add this workers to another list.
	 * 6. Each worker should reduce the models (thats ez) and save in an array of dimen n (n == no of days)
	 * 7. Iterate through the worker list and go joining them (so we can start 8. knowing all reducers finished
	 * their job)
	 * 8. Iterate the reducer and print its data
	 * 9. Dance ＼(￣ー＼)(／ー￣)／ ＼(￣ー＼)(／ー￣)／
	 */
	SocketManagerWorker managerWorker(socket, clientList);
	managerWorker.start();
}
