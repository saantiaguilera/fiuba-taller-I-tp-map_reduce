/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <list>
#include <string>
#include "server_Server.h"

Server::Server(std::string &port) {
	socket = new Socket();
	socket->bind(port);

	std::cout << "Binded" << std::endl;

	mappedDataList = new ConcurrentList<MapperModel*>();

	reducedDataList = new std::list<MapperModel*>();

	if (socket->connectivityState != CONNECTIVITY_OK)
		throw std::runtime_error("Cant bind!! (ﾉಥ益ಥ）ﾉ﻿ ┻━┻");
	//refactor this

	std::cout << "Initialized" << std::endl;
}

Server::~Server() {
	delete socket;

	//Size should be 0.
	delete mappedDataList;

	for (std::list<MapperModel*>::iterator it = reducedDataList->begin();
			it != reducedDataList->end(); ++it) {
		delete (*it);
	}

	reducedDataList->clear();

	delete reducedDataList;
}

void Server::receive() {
	bool *interrupted = new bool(false);
	std::string line;

	SocketManagerWorker managerWorker(socket, interrupted, mappedDataList);
	managerWorker.start();

	std::cout << "Forked thread for socket manager" << std::endl;

	while (!(*interrupted) && std::getline(std::cin, line)) {
		std::cout << "std::getLine:: " << line << std::endl;
		if (line == "q")
			(*interrupted) = true;
	}

	std::cout << "Q detected. Stop accepting connections" << std::endl;

	//Join the manager, which will join all his connections first
	managerWorker.join();

	std::cout << "All threads joined" << std::endl;

	delete interrupted;
}

void Server::reduce(std::list<ReducerWorker*> &list) {
	std::cout << "Joining threads" << std::endl;

	for (std::list<ReducerWorker*>::iterator it = list.begin();
			it != list.end(); ++it) {
		(*it)->join();
	}

	std::cout << "Finished joining, printing.." << std::endl;

	reducedDataList->sort(ReducerComparator::compare);
	for (std::list<ReducerModel*>::iterator it = reducedDataList->begin();
			it != reducedDataList->end(); ++it) {
		std::cout << (*it)->first << ": " << (*it)->second.first << " ("
				<< (*it)->second.second << ")" << std::endl;
	}
}

void Server::run() {
	/**
	 * DONE - 1. Spawn a worker that listens and accepts sockets.
	 * Save sockets in a list.
	 * DONE - 2. Each spawned worker should start recv data, for
	 * each model they parse, they append it to a
	 * thread safe list of day models
	 * DONE - 3. When server finds Q, interrupts the socket
	 * manager worker (find a workaround, interrupt is
	 * bad smell). Use a boolean shared element !!!  Goto 9.
	 * and return back in a while
	 * DONE - 4. Iterate through the socket list joining them
	 * (so we start 5. knowing all data is filled)
	 * DONE - 5. Iterate through the model list and go removing
	 * by id (like. first remove all day:1 and append it
	 * to another list). For each day spawn a worker with his
	 * according list. Add this workers to another list.
	 * DONE - 6. Each worker should reduce the models (thats ez)
	 * and save in an array of dimen n (n == no of days)
	 * DONE - 7. Iterate through the worker list and go joining
	 * them (so we can start 8. knowing all reducers finished
	 * their job)
	 * DONE - 8. Iterate the reducer and print its data
	 * DONE - 9. Dance ＼(￣ー＼)(／ー￣)／ ＼(￣ー＼)(／ー￣)／
	 */
	receive();

	std::cout << "Finished receiving" << std::endl;

	//At this point there are no race conditions.
	//Unblock the ConcurrentList and
	//use it as a normal one (so we can remove while iterating)
	std::list<MapperModel*> unblockedList = mappedDataList->unblock();

	std::list<ReducerWorker*> workersList;

	std::cout << "Created workers and unblocked list" << std::endl;

	std::cout << "Size of unblockedList is:: " << unblockedList.size()
			<< std::endl;

	while (unblockedList.size() != 0) {
		int dayToParse = -1;

		ReducerWorker *worker = new ReducerWorker();

		std::cout << "Created a reducer worker" << std::endl;

		for (std::list<MapperModel*>::iterator it = unblockedList.begin();
				it != unblockedList.end();) {
			if (dayToParse == -1) {
				//Grab the first day and lets spawn a
				//worker for all this same day
				dayToParse = (*it)->first;

				std::cout << "Appending to worker data from day:: "
						<< dayToParse << std::endl;
			}

			if (dayToParse == (*it)->first) {
				//If its the same type of day
				worker->addData((*it));

				it = unblockedList.erase(it);

				std::cout << "Value added." << std::endl;
			} else {
				++it;
			}

			std::cout << "Next value..." << std::endl;
		}

		std::cout << "Finished adding values." << std::endl;

		ReducerModel *reducerModel = new ReducerModel();

		reducedDataList->push_back(reducerModel);
		worker->attachResultContainer(reducerModel);

		worker->start();

		workersList.push_back(worker);

		std::cout << "Forked reducer for day:: " << dayToParse << std::endl;
	}

	//Reduce the list whilst printing
	reduce(workersList);

	std::cout << "All workers reduced" << std::endl;

	//Delete the idle threads in memory
	for (std::list<ReducerWorker*>::iterator it = workersList.begin();
			it != workersList.end(); ++it) {
		delete (*it);
	}
	workersList.clear();
}
