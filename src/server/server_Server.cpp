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

	dayList = new ConcurrentList<DayModel*>();

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

	ConcurrentList<DayModel*>::ConcurrentIterator dayIterator(dayList);
	for (std::list<DayModel*>::iterator it = dayIterator.begin() ;
			it != dayIterator.end() ; ++it) {
		delete (*it);
	}

	dayList->clear();

	delete dayList;
}

void Server::run() {
	/**
	 * DONE - 1. Spawn a worker that listens and accepts sockets. Save sockets in a list.
	 * DONE - 2. Each spawned worker should start recv data, for each model they parse, they append it to a
	 * thread safe list of day models
	 * DONE - 3. When server finds Q, interrupts the socket manager worker (find a workaround, interrupt is
	 * bad smell). Use a boolean shared element !!!  Goto 9. and return back in a while
	 * DONE - 4. Iterate through the socket list joining them (so we start 5. knowing all data is filled)
	 * 5. Iterate through the model list and go removing by id (like. first remove all day:1 and append it
	 * to another list). For each day spawn a worker with his according list. Add this workers to another list.
	 * 6. Each worker should reduce the models (thats ez) and save in an array of dimen n (n == no of days)
	 * 7. Iterate through the worker list and go joining them (so we can start 8. knowing all reducers finished
	 * their job)
	 * 8. Iterate the reducer and print its data
	 * 9. Dance ＼(￣ー＼)(／ー￣)／ ＼(￣ー＼)(／ー￣)／
	 */
	bool interrupted = false;
	std::string line;

	SocketManagerWorker managerWorker(socket, &interrupted, dayList);
	managerWorker.start();

	while (!interrupted && std::getline(std::cin, line))
		if (line == "q")
			interrupted = true;

	//Join the manager, which will join all his connections first
	managerWorker.join();
	//If we want to free some mem here, we can scope the manager and let
	//the scope finish here so he gets freed + all his threads and sockets.
	//I dont like braces in the middle of the code. Sorry wont happen.

}
