/*
 * Mutex.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef THREADING_COMMON_MUTEX_H_
#define THREADING_COMMON_MUTEX_H_

#include <cstdio>
#include <pthread.h>

/**
 * Simple class for a mutual exclusion
 */
class Mutex {
private:
	pthread_mutex_t mutex;

public:
	Mutex();

	void lock();
	void unlock();

	virtual ~Mutex();

private:
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);
};

#endif /* THREADING_COMMON_MUTEX_H_ */
