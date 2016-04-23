/*
 * common_SocketException.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <errno.h>
#include <cstring>
#include <string>
#include <iostream>
#include "common_SocketException.h"

/**
 * @Public
 * @Constructor
 *
 * As soon as its generated, it grabs the errno
 * and saves it (in case it changes before
 * using this exception)
 */
SocketException::SocketException(std::string message) throw() :
		std::exception(),
		message(message) {
	errorCode = errno;
}

/**
 * @Public
 * @Destructor
 */
SocketException::~SocketException() throw() {
}

/**
 * The what() message will be
 * the one used in the constructor
 */
const char * SocketException::what() const throw() {
	return message.c_str();
}

/**
 * Prints the what() + the errno
 */
void SocketException::print() const throw() {
	std::cout << "Error message: " << message << std::endl;
	std::cout << "Error details: " << strerror(errorCode) << std::endl;
}
