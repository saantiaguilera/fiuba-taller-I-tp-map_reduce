/*
 * client_Client.h
 *
 *  Created on: Apr 22, 2016
 *      Author: santiago
 */

#ifndef CLIENT_CLIENT_CLIENT_H_
#define CLIENT_CLIENT_CLIENT_H_

class Socket;

#include "../commons/common_MapperSerializer.h"
#include "../commons/common_MapperFileParser.h"
#include "../commons/common_MapperModel.h"
#include <string>

class Client {
private:
	Socket * socket;

	MapperFileParser * parser;
	MapperSerializer * serializer;

public:
	explicit Client(std::string &host, std::string &port);
	virtual ~Client();

	void run();

private:
	Client(const Client&);
	Client& operator=(const Client&);
};

#endif /* CLIENT_CLIENT_CLIENT_H_ */
