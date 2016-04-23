/*
 * Thread.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include "common_Thread.h"

#include <cstdio>
#include <pthread.h>


/**
 * @Public
 * @Constructor
 */
Thread::Thread() : thread() {
}

/**
 * @Public
 * @Destructor
 */
Thread::~Thread() {
}

/**
 * @Public
 * @Note: Joins this thread with the caller
 */
void Thread::join() {
    pthread_join(thread, NULL);
}

/**
 * @Public
 * @Note: Starts this thread and runs the
 * Runnable.
 */
void Thread::start() {
	pthread_create(&thread, NULL, Thread::runner, this);
}

/**
 * @Protected
 * @Note: This receives itself as a param
 * and invokes the run() method that acts
 * as a Runnable.
 *
 * @Returns the invoked thread
 */
void * Thread::runner(void *data) {
    Thread *self = (Thread*)data;
    self->run();
    return data;
}
