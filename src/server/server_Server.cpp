/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <list>
#include <string>
#include "server_Server.h"

//Code for stop listening for connections
#define QUIT "q"
#define MAX_WORKERS_SPAWN 4

/**
 * @Public
 * @Constructor
 *
 * @note: On construction it binds the socket to
 * a given port
 *
 * @throws SocketException if cant bind.
 */
Server::Server(std::string &port) {
	mappedDataList = new ConcurrentList<MapperModel*>();
	reducedDataList = new std::list<MapperModel*>();

	socket = new Socket();
	socket->bind(port);

	if (socket->connectivityState != CONNECTIVITY_OK)
		throw SocketException(
				"Server failed to bind to " + port);
}

/**
 * @Public
 * @Destructor
 */
Server::~Server() {
	delete socket;

	//Size should be 0.
	delete mappedDataList;

	for (std::list<MapperModel*>::iterator it = reducedDataList->begin();
			it != reducedDataList->end(); ++it) {
		delete (*it);
	}

	reducedDataList->clear();

	delete reducedDataList;
}

/**
 * @Private
 * @note: This method is in charge of the whole
 * receive operation of the thread.
 */
void Server::receive() {
	//Init variables we will be using
	/**
	 * Bool is in the heap since
	 * it will be a cut condition
	 * for the SocketManagerWorker
	 */
	bool *interrupted = new bool(false);
	std::string line;

	//Spawn a worker thread that manages connections
	/**
	 * Since socket is a shared element, we should
	 * use locks to prevent race conditions.
	 * But since this class only uses it in the
	 * constructor and destructor. And in the middle
	 * the manager. It cant present race conditions
	 * so currently no locks will be used.
	 *
	 * On the other hand, note that mappedDataList
	 * can present race conditions, so a RAII
	 * class was made
	 */
	SocketManagerWorker managerWorker(socket, interrupted, mappedDataList);
	managerWorker.start();

	//Freeze until the user enteres QUIT value
	while (!(*interrupted) && std::getline(std::cin, line))
		if (line == QUIT)
			(*interrupted) = true;

	//Join the manager, which will join all his connections first
	managerWorker.join();

	//Free used mem
	delete interrupted;
}

/**
 * @Private
 * @note This method is in charge of the
 * whole reduce operation.
 */
void Server::reduce(std::list<ReducerWorker*> &list) {
	//Join all the reducer workers
	for (std::list<ReducerWorker*>::iterator it = list.begin();
			it != list.end() ; ++it) {
		(*it)->join();
	}

	//Delete the idle threads in memory
	for (std::list<ReducerWorker*>::iterator it = list.begin();
			it != list.end(); ++it) {
		delete (*it);
	}
	list.clear();
}

/**
 * TO-DO LIST:
 * DONE - 1. Spawn a worker that listens and accepts sockets.
 * Save sockets in a list.
 * DONE - 2. Each spawned worker should start recv data, for
 * each model they parse, they append it to a
 * thread safe list of day models
 * DONE - 3. When server finds Q, using a  boolean shared
 * element, stop the manager and join him
 * DONE - 4. In the manager, iterate through the socket
 * list joining them (so we start 5. knowing all
 * data is filled)
 * DONE - 5. Iterate through the model list and go removing
 * by id (like. first remove all day:1 and append it
 * to another list). For each day spawn a worker with his
 * according list. Add this workers to another list.
 * DONE - 6. Each worker should reduce the models (thats ez)
 * and save its value in a list.
 * DONE - 7. Iterate through the worker list and go joining
 * them (so we can start 8. knowing all reducers finished
 * their job)
 * DONE - 8. Iterate the reducer and print its data
 * DONE - 9. Dance ＼(￣ー＼)(／ー￣)／ ＼(￣ー＼)(／ー￣)／
 */
/**
 * @Public
 * @note This method runs the whole server operation
 * A really simple explanation of what it does is:
 * 1. It spawns a worker that manages connections
 * 2. For each connection received
 * another worker is spawned that
 * receives data and parses it (stores it also in a
 * shared list)
 * 3. When we received the quit input we join all
 * the threads and stop accepting connections
 * 4. We reduce by key, being key the day field,
 * and each reducer is also spawned in another worker
 * 5. We join them all
 * 6. We print the data sorted.
 */
void Server::run() {
	//Do the whole receive stuff
	receive();

	//At this point there are no race conditions.
	//Unblock the ConcurrentList and
	//use it as a normal one (so we can remove while iterating)
	std::list<MapperModel*> unblockedList = mappedDataList->unblock();

	//Create a list for the reducers workers we will have
	std::list<ReducerWorker*> workersList;

	int threadsCreated = 0;

	//While there are still data elements without a worker assigned
	while (unblockedList.size() != 0) {
		int dayToParse = -1;

		//Create a worker
		ReducerWorker *worker = new ReducerWorker();

		/**
		 * Iterate through the whole list
		 * but only add to the worker the ones that
		 * are the same as the dayToParse
		 *
		 * @note: dayToParse will be setted with
		 * the first day it encounters.
		 *
		 * @note: Since this could be an inifinite
		 * loop, we remove them from this list
		 * since each worker will take care of
		 * them
		 */
		for (std::list<MapperModel*>::iterator it = unblockedList.begin();
				it != unblockedList.end();) {
			if (dayToParse == -1) {
				//Grab the first day and lets spawn a
				//worker for all this same day
				dayToParse = (*it)->first;
			}

			//If its the same type of day
			if (dayToParse == (*it)->first) {
				worker->addData((*it));

				it = unblockedList.erase(it);
			} else {
				++it;
			}
		}

		/**
		 * Create a reducer model and assign it
		 * to the worker (so he will set the
		 * values in this var)
		 * Also add this value to a dataList,
		 * which will be our "result" by the
		 * end of the program
		 *
		 * This value is a shared element,
		 * but since it will only use it
		 * the reducer thread, and after its join
		 * the main thread, it wont present
		 * currently races conditions.
		 * So no locks required.
		 */
		ReducerModel *reducerModel = new ReducerModel();

		reducedDataList->push_back(reducerModel);
		worker->attachResultContainer(reducerModel);

		//Start the worker and add it to a list
		worker->start();

		workersList.push_back(worker);

		if (threadsCreated == MAX_WORKERS_SPAWN) {
			/**
			 * 4 workers should be spawned
			 *
			 * Start reducing. (Its already reducing
			 * each worker, but this just waits
			 * for them to finish / joins / prints
			 * end results)
			 */
			reduce(workersList);

			threadsCreated = 0;
		} else {
			threadsCreated++;
		}
	}

	if (threadsCreated != 0)
		reduce(workersList);

	//Sort the list by day
	reducedDataList->sort(ReducerComparator::compare);

	//Print each day formatted accordingly
	for (std::list<ReducerModel*>::iterator it = reducedDataList->begin();
			it != reducedDataList->end(); ++it) {
		std::cout << (*it)->first << ": " << (*it)->second.first << " ("
				<< (*it)->second.second << ")" << std::endl;
	}
}
