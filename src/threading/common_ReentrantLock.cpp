/*
 * ReentrantLock.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include "common_ReentrantLock.h"

#include "common_Mutex.h"

/**
 * @Public
 * @Constructor
 * @Note: On instanciating this class
 * the scope will be locked and only
 * this thread is allowed to execute in it
 */
ReentrantLock::ReentrantLock(Mutex &m) : m(m) {
    m.lock();
}

/**
 * @Public
 * @Destructor
 * @Note: On destruction the lock is also
 * unlocked, so the scope is available
 * for other threads again
 */
ReentrantLock::~ReentrantLock() {
    m.unlock();
}
