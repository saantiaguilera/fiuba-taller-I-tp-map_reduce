/*
 * server_SocketReceiverWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "server_SocketReceiverWorker.h"

/**
 * @Public
 * @Constructor
 */
SocketReceiverWorker::SocketReceiverWorker(Socket *socket,
		ConcurrentList<MapperModel*> *list) :
		mainSocket(socket), postList(list) {
	parser = new MapperParser();
}

/**
 * @Public
 * @Destructor
 */
SocketReceiverWorker::~SocketReceiverWorker() {
	delete parser;
}

void SocketReceiverWorker::flush(std::string &buffer) {
	std::string line;
	while (buffer.find("\n") != std::string::npos) {
		//Get a line
		line = buffer.substr(0, buffer.find("\n") + 2); //TODO CHECK

		//If its not the End of the recv
		if (line.find("End") == std::string::npos) {
			//Create a day and put it in the list
			MapperModel *mappedModel = parser->parse(line);

			postList->add(mappedModel);

			std::cout << "Model hidrated:: " << mappedModel->first << " " << mappedModel->second.first << " " << mappedModel->second.second << std::endl;
		}

		//Remove line from buffer
		buffer = buffer.substr(buffer.find("\n") + 2);
	}
	//Note that if socket sends a partial line the buffer
	//Will still have some data on
}

void SocketReceiverWorker::run() {
	bool done = false;
	REQUEST_STATE state = REQUEST_RECEIVING_DATA;
	std::string total;

	char recvbuf[64];

	while (!done &&
			state != REQUEST_ERROR) {
		//Receive the code of the request
		state = mainSocket->receive(&recvbuf[0],
				64);

		//Check for errors
		if (state == REQUEST_ERROR) {
			printf("Error receiving\n");
		} else {
			total.append(recvbuf);

			std::cout << "Received:: " << std::endl << total << std::endl;

			if (total.find("End\n") != std::string::npos)
				done = true;

			flush(total);
		}
	}
}
