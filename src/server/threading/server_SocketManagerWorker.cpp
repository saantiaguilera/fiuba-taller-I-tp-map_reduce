/*
 * server_SocketManagerWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "server_SocketManagerWorker.h"

/**
 * @Public
 * @Constructor
 */
SocketManagerWorker::SocketManagerWorker(Socket *socket,
		bool *interrupted,
		ConcurrentList<DayModel*> * dayList) :
		mainSocket(socket), interrupted(interrupted),
		dayList(dayList) {
	socketList = new std::list<Socket*>();
	threadList = new std::list<Thread*>();
	mainSocket->listen(SOMAXCONN);
	//Dunno how many will be, use max available by man page
}

/**
 * @Public
 * @Destructor
 */
SocketManagerWorker::~SocketManagerWorker() {
	for (std::list<Socket*>::iterator it = socketList->begin() ;
			it != socketList->end() ; ++it) {
		delete (*it);
	}

	socketList->clear();

	delete socketList;


	for (std::list<Thread*>::iterator it = threadList->begin() ;
			it != threadList->end() ; ++it) {
		delete (*it);
	}

	threadList->clear();

	delete threadList;
}

void SocketManagerWorker::run() {
	while (!(*interrupted)) {
		//Maybe we could use a sleep here so it doesnt do
		//So much activity?

		//Note that this accept is nonblocking.
		Socket *clientSocket = mainSocket->accept();

		if (clientSocket->connectivityState != CONNECTIVITY_ERROR) {
			socketList->push_back(clientSocket);

			//Spawn him a thread and let him work
			SocketReceiverWorker *worker = new SocketReceiverWorker(clientSocket, dayList);
			worker->start();

			threadList->push_back(worker);
		} else delete clientSocket; //There was an error, delete alloc mem
	}

	//We got interrupted. Start joining
	for (std::list<Thread*>::iterator it = threadList->begin() ;
			it != threadList->end() ; ++it) {
		(*it)->join();
	}

	//We are done. Let us be merged, peace out !
}
