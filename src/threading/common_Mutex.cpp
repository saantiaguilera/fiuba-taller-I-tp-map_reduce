/*
 * Mutex.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include "common_Mutex.h"

/**
 * @Public
 * @Constructor
 * @Note, initializes the mutex
 */
Mutex::Mutex() {
	pthread_mutex_init(&this->mutex, NULL);
}

/**
 * @Public
 * @Destructor
 * @Note: Destroys the mutex
 */
Mutex::~Mutex() {
	pthread_mutex_destroy(&this->mutex);
}

/**
 * @Public
 * @Note: Locks the scope for only a thread
 */
void Mutex::lock() {
	pthread_mutex_lock(&this->mutex);
}

/**
 * @Public
 * @Note: Unlocks the scope
 */
void Mutex::unlock() {
	pthread_mutex_unlock(&this->mutex);
}
