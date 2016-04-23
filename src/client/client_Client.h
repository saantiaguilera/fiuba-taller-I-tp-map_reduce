/*
 * client_Client.h
 *
 *  Created on: Apr 22, 2016
 *      Author: santiago
 */

#ifndef CLIENT_CLIENT_CLIENT_H_
#define CLIENT_CLIENT_CLIENT_H_

class Socket;

#include "../commons/DaySerializer.h"
#include "../commons/DayFileParser.h"
#include "../commons/DayModel.h"
#include <string>

class Client {
private:
	Socket * socket;

	DayFileParser * parser;
	DaySerializer * serializer;

public:
	explicit Client(std::string &host, std::string &port);
	virtual ~Client();

	void run();

private:
	Client(const Client&);
	Client& operator=(const Client&);
};

#endif /* CLIENT_CLIENT_CLIENT_H_ */
