/*
 * ParserWorkerThread.h
 *
 *  Created on: Apr 9, 2016
 *      Author: santiago
 */

#ifndef PARSERWORKERTHREAD_H_
#define PARSERWORKERTHREAD_H_

#include <pthread.h>

/**
 * Worker thread class for the parser
 */
class ParserWorker: public Thread {
private:
	ParserWorker(const ParserWorker&);
	ParserWorker& operator=(const ParserWorker&);

protected:
	virtual void run();

public:
	explicit ParserWorker();
	virtual ~ParserWorker();
};

#endif /* PARSERWORKERTHREAD_H_ */
