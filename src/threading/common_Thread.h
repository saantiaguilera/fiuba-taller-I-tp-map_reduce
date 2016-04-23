/*
 * Thread.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

/**
 * Simple abstract thread class that is able
 * to be started or joined
 */
class Thread {
private:
	pthread_t thread;

	static void *runner(void *data);

protected:
	virtual void run() = 0;

public:
	Thread();

	void start();
	void join();

	virtual ~Thread();

private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

#endif /* THREAD_H_ */
