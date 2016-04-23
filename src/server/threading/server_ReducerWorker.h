/*
 * server_SocketReducerWorker.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_THREADING_SERVER_REDUCERWORKER_H_
#define SERVER_THREADING_SERVER_REDUCERWORKER_H_

#include <list>
#include <pthread.h>

#include "../../commons/common_ReducerModel.h"
#include "../../commons/common_MapperModel.h"
#include "../../socket/common_Socket.h"
#include "../../threading/common_Mutex.h"

#include "../../threading/common_Thread.h"
#include "../../commons/common_ThreadsafeList.h"

/**
 * Worker thread class for a particular server reducer
 */
class ReducerWorker: public Thread {
private:
	std::list<MapperModel*> *collection;

	ReducerModel *resultContainer;

protected:
	virtual void run();

public:
	ReducerWorker();

	void attachResultContainer(ReducerModel *container);
	void addData(MapperModel *data);

	virtual ~ReducerWorker();

private:
	ReducerWorker(const ReducerWorker&);
	ReducerWorker& operator=(const ReducerWorker&);
};

#endif /* SERVER_THREADING_SERVER_REDUCERWORKER_H_ */
