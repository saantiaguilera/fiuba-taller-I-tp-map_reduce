/*
 * server_SocketManagerWorker.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_THREADING_SERVER_SOCKETMANAGERWORKER_H_
#define SERVER_THREADING_SERVER_SOCKETMANAGERWORKER_H_

#include <list>
#include <pthread.h>
#include "../../socket/common_Socket.h"
#include "../../threading/common_Mutex.h"

#include "../../threading/common_Thread.h"
#include "../../commons/common_ThreadsafeList.h"

/**
 * Worker thread class for the socket manager
 */
class SocketManagerWorker: public Thread {
private:
	Socket * mainSocket;
	ConcurrentList<Socket*> * socketList;

protected:
	virtual void run();

public:
	explicit SocketManagerWorker(Socket *socket, ConcurrentList<Socket*> * list);
	virtual ~SocketManagerWorker();

private:
	SocketManagerWorker(const SocketManagerWorker&);
	SocketManagerWorker& operator=(const SocketManagerWorker&);
};

#endif /* SERVER_THREADING_SERVER_SOCKETMANAGERWORKER_H_ */
