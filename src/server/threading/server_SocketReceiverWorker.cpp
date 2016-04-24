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

/**
 * @Private
 * @note flushes a buffer creating all the possible
 * data in it.
 *
 * @note buffer can still contain data by the end of
 * this method
 *
 * Eg. buffer has only "2 BuenosAi", (its incomplete)
 * it wont be parsed and will be left in buffer.
 * Until a new flush has it complete.
 */
void SocketReceiverWorker::flush(std::string &buffer) {
	//Init stack vars we will be using
	std::string line;
	bool stop = false;

	//As long as there are new lines and !stopping
	while (!stop && buffer.find("\n") != std::string::npos) {
		//Get a line
		line = buffer.substr(0, buffer.find("\n") + 1);

		//If its not the End, defined by the protocol
		if (line.find("End") == std::string::npos) {
			//Create a day and put it in the list
			MapperModel *mappedModel = parser->parse(line);
			postList->add(mappedModel);
		} else {
			stop = true; //We are in the end. Stop
		}

		/**
		 * Some files from the data sample contains
		 * at the end empty lines. As workaround for
		 * this issue we are using this boolean
		 * +
		 * In the client we are validating the line
		 * isnt empty
		 */

		//Remove line from buffer
		buffer = buffer.substr(buffer.find("\n") + 1);
	}
	//Note that if socket sends a partial line the buffer
	//Will still have some data on
}

void SocketReceiverWorker::run() {
	//Init stuff
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
		 * I didnt created a particular exception because
		 * time isnt on my side
		 * (I need to create a global exception that the main ui
		 * catches it or send a signal and also the main ui catches
		 * it). I would go for the first one :)
		 */
		if (state == REQUEST_ERROR) {
			done = true;
			std::cout << "Error while receiving data" << std::endl;
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else {
			//Append the received data to the total
			total.append(std::string(recvbuf));

			//If End protocol appears in the string, stop iterating
			if (total.find("End\n") != std::string::npos)
				done = true;

			//Flush our buffer
			flush(total);
		}
	}
}
