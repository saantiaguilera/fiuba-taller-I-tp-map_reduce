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
#include "server_SocketReceiverWorker.h"
#include "../../socket/common_Socket.h"
#include "../../threading/common_Mutex.h"
#include "../../commons/common_MapperModel.h"

#include "../../threading/common_Thread.h"
#include "../../commons/common_ThreadsafeList.h"

/**
 * Worker thread class for the socket manager
 *
 * We keep track of two things
 * - Sockets created (RAII). We are the ones
 * in charge of the sockets
 * since we created them. So when we finish
 * joining all the threads we
 * just delete the sockets
 *
 * - Threads spawned. We will be joining all
 * of them and of course
 * deleting.
 *
 * @note: Only the dayList can present race conditions
 * since it will be accessed from more than one thread.
 *
 * The socket list and the thread list
 * only this class can access it
 * so it wont present race conditions,
 * so for faster and eficient stuff
 * we wont be using a ConcurrentList instance
 */
class SocketManagerWorker: public Thread {
private:
	Socket * mainSocket;
	std::list<Socket*> * socketList;
	std::list<Thread*> * threadList;

	bool *interrupted;

	ConcurrentList<MapperModel*> * mapperDataList;

protected:
	virtual void run();

public:
	explicit SocketManagerWorker(Socket *socket, bool *interrupted,
			ConcurrentList<MapperModel*> * mapperDataList);
	virtual ~SocketManagerWorker();

private:
	SocketManagerWorker(const SocketManagerWorker&);
	SocketManagerWorker& operator=(const SocketManagerWorker&);
};

#endif /* SERVER_THREADING_SERVER_SOCKETMANAGERWORKER_H_ */
