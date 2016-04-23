/*
 * common_Socket.h
 *
 *  Created on: Apr 22, 2016
 *      Author: santiago
 */

#ifndef SOCKET_COMMON_SOCKET_H_
#define SOCKET_COMMON_SOCKET_H_

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <string>

//Definitions for knowing what the possible filter values are
#define IPv4 AF_INET
#define IPv6 AF_INET6
#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM
#define LOCALHOST AI_PASSIVE

typedef enum REQUEST_STATE {
	REQUEST_RECEIVING_DATA = 1,
	REQUEST_SOCKET_CLOSED = 0,
	REQUEST_ERROR = -1
} REQUEST_STATE;
//Enum for request states
//(aka know the return state of a send or receive)

typedef enum CONNECTIVITY_STATE {
	CONNECTIVITY_OK = 0,
	CONNECTIVITY_ERROR = -1,
	CONNECTIVITY_UNDEFINED = -2
} CONNECTIVITY_STATE;
//Enum for connection state
//(aka know the return state of a connect / listen or bind)

typedef struct addrinfo addrinfo_t;
//For not having to type always struct addrinfo :)

class Socket {
private:
	int mSocket;
	CONNECTIVITY_STATE connectivityState;

public:
	Socket();
	~Socket();

	void connect(std::string &hostName, std::string &port);
	void bind(std::string &hostName, std::string &port);

	void listen(int listeners);
	Socket * accept();

	REQUEST_STATE send(std::string &messageData,
			size_t buffLength);
	REQUEST_STATE receive(std::string &response,
			size_t buffLength);

private:
	addrinfo_t* getAddrInfo(std::string &hostName, std::string &port);
	void shutdown();
	void close();
};

#endif /* SOCKET_COMMON_SOCKET_H_ */
