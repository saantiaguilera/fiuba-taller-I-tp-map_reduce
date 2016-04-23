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

SocketException::SocketException(std::string message) throw() :
		std::exception(),
		message(message) {
	errorCode = errno;
}

SocketException::~SocketException() throw() {
}

const char * SocketException::what() const throw() {
	return message.c_str();
}

void SocketException::print() const throw() {
	std::cout << "Error message: " << message << std::endl;
	std::cout << "Error details: " << strerror(errorCode) << std::endl;
}
