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
		ConcurrentList<MapperModel*> * mapperDataList) :
		mainSocket(socket), interrupted(interrupted),
		mapperDataList(mapperDataList) {
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
		std::cout << "Connecting..." << std::endl;

		int queueConnections = mainSocket->select();

		if (queueConnections > 0) {
			for (int i = 0 ; i < queueConnections ; ++i) {
				Socket *clientSocket = mainSocket->accept();

				if (clientSocket->connectivityState != CONNECTIVITY_ERROR) {
					std::cout << "Connection accepted in SM" << std::endl;

					socketList->push_back(clientSocket);

					//Spawn him a thread and let him work
					SocketReceiverWorker *worker = new SocketReceiverWorker(clientSocket, mapperDataList);
					worker->start();

					threadList->push_back(worker);

					std::cout << "Forked new thread for the connection" << std::endl;
				} else delete clientSocket; //There was an error, delete alloc mem
			}
		}
	}

	std::cout << "interruption in SM, joining connections" << std::endl;

	//We got interrupted. Start joining
	for (std::list<Thread*>::iterator it = threadList->begin() ;
			it != threadList->end() ; ++it) {
		(*it)->join();
	}

	std::cout << "All threads joined from SM" << std::endl;

	//We are done. Let us be merged, peace out !
}
