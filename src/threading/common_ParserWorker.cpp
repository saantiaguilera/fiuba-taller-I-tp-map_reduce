/*
 * ParserWorker.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
#include <list>
#include <map>
#include <stdexcept>

class Expression;

#include "common_Mutex.h"

#include <pthread.h>
#include "common_Thread.h"
#include "common_ParserWorker.h"

/**
 * @Public
 * @Constructor
 */
ParserWorker::ParserWorker() {
}

/**
 * @Public
 * @Destructor
 */
ParserWorker::~ParserWorker() {

}

/**
 * @Protected
 * @Note: Evaluates the expression
 */
void ParserWorker::run() {
}
