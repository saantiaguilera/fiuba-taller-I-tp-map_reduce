/*
 * server_Server.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_SERVER_SERVER_H_
#define SERVER_SERVER_SERVER_H_

#include "../commons/common_ThreadsafeList.h"
#include "../commons/common_MapperModel.h"
#include "../commons/common_ReducerModel.h"
#include "../threading/common_Mutex.h"
#include "../threading/common_Thread.h"
#include "../socket/common_Socket.h"
#include "misc/server_ReducerComparator.h"
#include "../socket/common_SocketException.h"
#include <iostream>
#include "stdexcept"
#include <list>
#include "threading/server_SocketManagerWorker.h"
#include <string>
#include "threading/server_ReducerWorker.h"
#include "../commons/common_MapperParser.h"
#include "../commons/common_MapperSerializer.h"

class Server {
private:
	Socket * socket;

	ConcurrentList<MapperModel*> * mappedDataList;
	std::list<ReducerModel*> * reducedDataList;

public:
	explicit Server(std::string &port);
	virtual ~Server();

	void run();

private:
	Server(const Server&);
	Server& operator=(const Server&);

	void receive();
	void reduce(std::list<ReducerWorker*> &workers);
};

#endif /* SERVER_SERVER_SERVER_H_ */
