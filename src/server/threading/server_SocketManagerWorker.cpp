/*
 * server_SocketManagerWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <list>
#include "server_SocketManagerWorker.h"

/**
 * @Public
 * @Constructor
 */
SocketManagerWorker::SocketManagerWorker(Socket *socket, bool *interrupted,
		ConcurrentList<MapperModel*> * mapperDataList) :
		mainSocket(socket), interrupted(interrupted), mapperDataList(
				mapperDataList) {
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
	for (std::list<Socket*>::iterator it = socketList->begin();
			it != socketList->end(); ++it) {
		delete (*it);
	}

	socketList->clear();

	delete socketList;

	for (std::list<Thread*>::iterator it = threadList->begin();
			it != threadList->end(); ++it) {
		delete (*it);
	}

	threadList->clear();

	delete threadList;
}

void SocketManagerWorker::run() {
	//As long as the main thread doesnt interrupt us
	while (!(*interrupted)) {
		/**
		 * I didnt created a particular exception because time
		 * isnt on my side
		 * (I need to create a global exception that the main ui
		 * catches it or send a signal and also the main ui catches
		 * it). I would go for the first one :)
		 * This applies for:
		 * select()
		 * accept()
		 */
		/**
		 * If we just use accept, we will freeze the thread
		 * and if the main ui tries to joins us (changing
		 * the interrupt flag) but there are not more
		 * connections, we will never join.
		 *
		 * So we use select with a 10second timeout to
		 * check for available connecitons
		 */
		int queueConnections = mainSocket->select();

		if (queueConnections > 0) {
			//Loop through all the connections available
			for (int i = 0; i < queueConnections; ++i) {
				//Accept 'em all
				Socket *clientSocket = mainSocket->accept();

				if (clientSocket->connectivityState != CONNECTIVITY_ERROR) {
					socketList->push_back(clientSocket);

					//Spawn him a thread and let him work
					SocketReceiverWorker *worker = new SocketReceiverWorker(
							clientSocket, mapperDataList);
					worker->start();

					threadList->push_back(worker);
				} else {
					delete clientSocket; //There was an error, delete alloc mem
				}
			}
		}
	}

	//We got interrupted. Start joining
	for (std::list<Thread*>::iterator it = threadList->begin();
			it != threadList->end(); ++it) {
		(*it)->join();
	}
	//We are done. Let us be merged, peace out !
}
