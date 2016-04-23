/*
 * common_Socket.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: santiago
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include "errno.h"
#include <iostream>
#include <cstdio>
#include "common_Socket.h"

/**
 * Init for a given socket
 * @note: From start the connectivity will be undefined, try
 * not to handle actions (either for an error or success) in
 * this state
 */
Socket::Socket() {
	this->mSocket = 0;
	this->connectivityState = CONNECTIVITY_UNDEFINED;
}

/**
 * Destructor
 * @note: We will try to shutdown and close the socket (for
 * flushing data and closing the conn) in case it wasnt done
 * @note: As init, connection state will be set as undefined
 */
Socket::~Socket() {
	Socket::shutdown();
	Socket::close();

	this->connectivityState = CONNECTIVITY_UNDEFINED;
}

/**
 * Get the address info of a given hostname and port
 *
 * @note: This is intended be a private method, so its your fault
 * if you use it !
 *
 * @note: We will be using as default (and static, sorry) IPv4,
 * TCP and LocalHost for filters
 *
 * @side: client/server
 *
 * @returns addrinfo_t* with the available address to connect
 * @see connectivityState in socket_t* for the connection state
 */
addrinfo_t* Socket::getAddrInfo(std::string &hostName, std::string &port) {
	//Vars we will be using
	int state;
	addrinfo_t hints;
	addrinfo_t *result;

	//Clear the hints struct (or fill it with 0 ?)
	memset(&hints, 0, sizeof(addrinfo_t));
	//Set the config we will be using
	hints.ai_family = IPv4;
	hints.ai_socktype = TCP;

	/**
	 * If ai_flags is AI_PASSIVE (LocalHost) use hostName = NULL
	 * Else ai_flags set it to zero and use whatever hostName u want
	 * (beware you cant do "127.0.0.1")
	 */
	std::string localHost = "127.0.0.1";

	if (hostName != localHost)
		hints.ai_flags = LOCALHOST;
	else
		hints.ai_flags = 0;

	//Get the addrinfo of it (inside results).
	state = getaddrinfo(hostName.c_str(), port.c_str(), &hints, &result);

	//If error, set it in the socket connection and return NULL
	if (state != 0) {
		std::cout << "Error in getaddrinfo: %s\n" << gai_strerror(state) << std::endl;
		connectivityState = CONNECTIVITY_ERROR;
		return NULL;
	}

	//Else everything went fine, return the results of the getAddrInfo();
	connectivityState = CONNECTIVITY_OK;

	return result;
}

/**
 * Connects to the given hostname:port.
 * This automatically gets the address available
 *
 * @side: client
 * @see: connectivityState in socket_t* for the connection state
 * @note: This is a "pause" method. Meaning the thread will
 * freeze as long as a connection doesnt open
 */
void Socket::connect(std::string &hostName, std::string &port) {
	//Init vars
	addrinfo_t *results, *ptr;
	int state;
	bool connected = false;

	//Get the addrinfo (@note: Might throw NULL)
	results = getAddrInfo(hostName, port);

	//Avoid the @NullPointerException
	if(connectivityState != CONNECTIVITY_OK)
		return;

	//Iterate through all of our possible address,
	//create a socket with the config and try to connect
	for (ptr = results; ptr != NULL && !connected; ptr = ptr->ai_next) {
		this->mSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (mSocket == CONNECTIVITY_ERROR) {
			//We got an error, this address is down so try with the next
			connectivityState = CONNECTIVITY_ERROR;
			std::cout << "Error: %s\n" << strerror(errno) << std::endl;
		} else {
			//Address went fine, lets try to connect
			state = ::connect(mSocket, ptr->ai_addr, ptr->ai_addrlen);

			if (state == CONNECTIVITY_ERROR) {
				//Coudlnt connect (502?). Close the socket and try with the next
				connectivityState = CONNECTIVITY_ERROR;
				std::cout << "Error: %s\n" << strerror(errno) << std::endl;
	            Socket::close();
			}

			//If we could connect, stop trying. We are connected
			connected = (state != CONNECTIVITY_ERROR);
		}
	}

	//Free used mem
	freeaddrinfo(results);
}

/**
 * Bind the socket to a given host:port
 *
 * @side: server
 * @see: connectivityState in socket_t* for the connection state
 */
void Socket::bind(std::string &hostName, std::string &port) {
	//Get the address info
	addrinfo_t *result = getAddrInfo(hostName, port);

	//Check against the NullPointerExcep
	if(connectivityState != CONNECTIVITY_OK)
		return;

	//Create a socket and bind to it
	mSocket = socket(result->ai_family,
					result->ai_socktype,
					result->ai_protocol);

	switch (::bind(mSocket,
			result->ai_addr,
			result->ai_addrlen)) {
		case CONNECTIVITY_OK:
			connectivityState = CONNECTIVITY_OK;
			break;

		case CONNECTIVITY_ERROR:
			connectivityState = CONNECTIVITY_ERROR;
			break;

		case CONNECTIVITY_UNDEFINED:
			connectivityState = CONNECTIVITY_UNDEFINED;
	}

	//Free used mem
    freeaddrinfo(result);

    if (connectivityState == CONNECTIVITY_ERROR) {
    	//If we couldnt bind, close the socket and return
    	std::cout << "Error: %s\n" << strerror(errno) << std::endl;
    	Socket::close();
    	return;
    }

    //If we are here it means we made it!
    connectivityState = CONNECTIVITY_OK;
}

/**
 * Start listening to the binded thread
 *
 * @side: server
 * @requires: socket binded to a host:port
 * @see: connectivityState in socket_t* for the connection state
 * @note: This is a "pause" method. Meaning the
 * thread will freeze as long as a connection doesnt open
 */
void Socket::listen(int listeners) {
	//Start listening
	int response = ::listen(mSocket, listeners);

	if (response == CONNECTIVITY_ERROR) {
		//We got an error trying to listen, close the socket
		std::cout << "Error: %s\n" << strerror(errno) << std::endl;
		Socket::close();
		connectivityState = CONNECTIVITY_ERROR;
	}
}

Socket * Socket::accept() {
	Socket *socket = new Socket();

	//Freeze the thread, try connecting
	socket->mSocket = ::accept(mSocket, NULL, NULL);

	if (socket->mSocket == CONNECTIVITY_ERROR) {
		//Damn, an error
		std::cout << "Error: %s\n" << strerror(errno) << std::endl;
		socket->connectivityState =  CONNECTIVITY_ERROR;
	} else {
		//We did it!
		socket->connectivityState =  CONNECTIVITY_OK;
	}

	return socket;
}

/**
 * Send data through the connection
 *
 * @param messageData is the data to send
 * @param buffLength is the length of the messageData
 *
 * @side: client/server
 * @requires: socket connection to a host:name opened
 *
 * @returns REQUEST_STATE with the state of the "transaction"
 */
REQUEST_STATE Socket::send(std::string &messageData,
		size_t buffLength) {
	//Init vars
	int sendResponse = 0;
	REQUEST_STATE state = REQUEST_RECEIVING_DATA;
	//TODO refactor ? It should have a OK enum
	int bytesSent = 0;

	//As long as the bytes sent arent more than
	//our length,  or the request suffered
	//something, keep trying
	while (bytesSent < buffLength &&
			state == REQUEST_RECEIVING_DATA) {
		sendResponse = ::send(mSocket,
				&messageData[bytesSent],
				buffLength - bytesSent,
				MSG_NOSIGNAL);

		if (sendResponse < 0) {
			state = REQUEST_ERROR;
		} else {
			if (sendResponse == 0)
				state = REQUEST_SOCKET_CLOSED;
			else
				bytesSent += sendResponse;
		}
	}

	//If our state mutated (not good), shutdown and close the socket
	if (state != REQUEST_RECEIVING_DATA) {
		Socket::shutdown();
		Socket::close();
	}

	return state;
}


/**
 * Receive data through the connection
 *
 * @param response is where the data will be written
 * @param buffLength is the length of the response you expect
 *
 * @side: client/server
 * @requires: socket connection to a host:name opened
 *
 * @returns REQUEST_STATE with the state of the "transaction"
 */
REQUEST_STATE Socket::receive(std::string &response,
		size_t buffLength) {
	//Init vars
	int sendResponse = 0;
	REQUEST_STATE state = REQUEST_RECEIVING_DATA;
	int bytesReceived = 0;

	//As long as we are still receiving data,
	//and our bytes received arent more than
	//our max capacity, keep receiving
	while (state == REQUEST_RECEIVING_DATA && bytesReceived < buffLength) {
		sendResponse = ::recv(mSocket,
				&response[bytesReceived],
				buffLength - bytesReceived,
				MSG_NOSIGNAL);

		if (sendResponse < 0) {
			state = REQUEST_ERROR;
		} else {
			if (sendResponse == 0)
				state = REQUEST_SOCKET_CLOSED;
			else
				bytesReceived += sendResponse;
		}
	}

	return state;
}

/**
 * @side: client/server
 * Shutdowns a socket (fd)
 */
void Socket::shutdown() {
	::shutdown(mSocket, SHUT_RDWR);
}

/**
 * @side: client/server
 * Closes a socket (fd)
 */
void Socket::close() {
	::close(mSocket);
	mSocket = -1;
}



