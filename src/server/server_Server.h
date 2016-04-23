/*
 * server_Server.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_SERVER_SERVER_H_
#define SERVER_SERVER_SERVER_H_

class Socket;

#include "../commons/common_DaySerializer.h"
#include "../commons/common_DayParser.h"
#include "../commons/common_DayModel.h"
#include <string>

class Server {
private:
	Socket * socket;

	DayParser * parser;
	DaySerializer * serializer;

public:
	explicit Server(std::string &port);
	virtual ~Server();

	void run();

private:
	Server(const Server&);
	Server& operator=(const Server&);
};

#endif /* SERVER_SERVER_SERVER_H_ */
