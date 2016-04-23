/*
 * server_SocketReceiverWorker.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_THREADING_SERVER_SOCKETRECEIVERWORKER_H_
#define SERVER_THREADING_SERVER_SOCKETRECEIVERWORKER_H_

#include <list>
#include <pthread.h>
#include "../../commons/common_DayModel.h"
#include "../../socket/common_Socket.h"
#include "../../threading/common_Mutex.h"
#include "../../commons/common_DayParser.h"

#include "../../threading/common_Thread.h"
#include "../../commons/common_ThreadsafeList.h"

/**
 * Worker thread class for a particular server receiver socket
 */
class SocketReceiverWorker: public Thread {
private:
	Socket * mainSocket;
	ConcurrentList<DayModel*> * postList;
	DayParser * parser;

	void flush(std::string &line);
protected:
	virtual void run();

public:
	explicit SocketReceiverWorker(Socket *socket, ConcurrentList<DayModel*> * list);
	virtual ~SocketReceiverWorker();

private:
	SocketReceiverWorker(const SocketReceiverWorker&);
	SocketReceiverWorker& operator=(const SocketReceiverWorker&);
};

#endif /* SERVER_THREADING_SERVER_SOCKETRECEIVERWORKER_H_ */
