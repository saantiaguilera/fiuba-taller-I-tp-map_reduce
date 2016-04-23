/*
 * server_SocketReceiverWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <string>
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
	bool stop = false;

	while (!stop && buffer.find("\n") != std::string::npos) {
		//Get a line
		line = buffer.substr(0, buffer.find("\n") + 1);

		//If its not the End of the recv
		if (line.find("End") == std::string::npos) {
			//Create a day and put it in the list
			MapperModel *mappedModel = parser->parse(line);

			postList->add(mappedModel);
		} else {
			stop = true; //We are in the end.
		}

		//Remove line from buffer
		buffer = buffer.substr(buffer.find("\n") + 1);
	}
	//Note that if socket sends a partial line the buffer
	//Will still have some data on
}

void SocketReceiverWorker::run() {
	bool done = false;
	REQUEST_STATE state = REQUEST_RECEIVING_DATA;
	std::string total;

	char recvbuf[65];
	recvbuf[64] = 0; //To avoid overflow
	//Although receive already does this, but
	//valgrind still complaints

	while (!done && state != REQUEST_ERROR) {
		//Receive the code of the request
		state = mainSocket->receive(&recvbuf[0], 64);

		//Check for errors.
		/**
		 * There wont be an exception because time isnt on my side
		 * (I need to create a global exception that the main ui
		 * catches it or send a signal and also the main ui catches
		 * it). I would go for the first one :)
		 */
		if (state == REQUEST_ERROR) {
			done = true;
			std::cout << "Error while receiving data" << std::endl;
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else {
			total.append(std::string(recvbuf));

			//std::cout << "Received:: " << std::endl << total << std::endl;

			if (total.find("End\n") != std::string::npos)
				done = true;

			flush(total);
		}
	}
}
