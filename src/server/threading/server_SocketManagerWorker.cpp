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
		ConcurrentList<Socket*> *list) :
		mainSocket(socket), socketList(list) {
	mainSocket->listen(SOMAXCONN);
	//Dunno how many will be, use max available by man page
}

/**
 * @Public
 * @Destructor
 */
SocketManagerWorker::~SocketManagerWorker() {

}

void SocketManagerWorker::run() {
	while (1) {
		Socket *clientSocket = mainSocket->accept();

		if (clientSocket->connectivityState != CONNECTIVITY_ERROR) {
			socketList->add(clientSocket);

			//Spawn him a thread and let him work
		}
	}
}
