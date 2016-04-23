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
		ConcurrentList<DayModel*> * dayList) :
		mainSocket(socket), dayList(dayList) {
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
	while (1) {
		Socket *clientSocket = mainSocket->accept();

		if (clientSocket->connectivityState != CONNECTIVITY_ERROR) {
			socketList->push_back(clientSocket);

			//Spawn him a thread and let him work
			SocketReceiverWorker *worker = new SocketReceiverWorker(clientSocket, dayList);
			worker->start();

			threadList->push_back(worker);
		}
	}
}
