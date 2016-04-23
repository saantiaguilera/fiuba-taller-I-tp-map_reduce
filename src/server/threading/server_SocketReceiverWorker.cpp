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
		ConcurrentList<DayModel*> *list) :
		mainSocket(socket), postList(list) {
	parser = new DayParser();
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
			DayModel *day = parser->parse(line);

			postList->add(day);
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
	std::string buffer, total;

	while (!done &&
			state != REQUEST_ERROR) {
		//Receive the code of the request
		state = mainSocket->receive(buffer,
				64);

		//Check for errors
		if (state == REQUEST_ERROR) {
			printf("Error receiving\n");
		} else {
			total.append(buffer);
			buffer.clear();

			if (total.find("End\n") == std::string::npos)
				done = true;

			flush(total);
		}
	}
}