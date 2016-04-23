/*
 * common_SocketException.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SOCKET_COMMON_SOCKETEXCEPTION_H_
#define SOCKET_COMMON_SOCKETEXCEPTION_H_

#include <cstring>
#include <errno.h>
#include <iostream>
#include <string>
#include <exception>

/**
 * Exception class for the socket.
 */
class SocketException: public std::exception {
	private:
		std::string message;
		int errorCode;

	public:
		explicit SocketException(std::string message) throw();
		SocketException(const SocketException&);
		virtual ~SocketException() throw();

		virtual const char *what() const throw();
		void print() const throw();

	private:
		SocketException& operator=(const SocketException&);
};

#endif /* SOCKET_COMMON_SOCKETEXCEPTION_H_ */
