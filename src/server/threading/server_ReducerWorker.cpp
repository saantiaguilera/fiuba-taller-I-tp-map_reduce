/*
 * server_SocketReducerWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */


#include "server_ReducerWorker.h"

/**
 * @Public
 * @Constructor
 */
ReducerWorker::ReducerWorker() {
	resultContainer = NULL;
	collection = new std::list<MapperModel*>();
}

/**
 * @Public
 * @Destructor
 */
ReducerWorker::~ReducerWorker() {
	for (std::list<MapperModel*>::iterator it = collection->begin() ;
			it != collection->end() ; ++it) {
		delete (*it);
	}

	collection->clear();

	delete collection;
}

void ReducerWorker::attachResultContainer(ReducerModel *resultContainer) {
	this->resultContainer = resultContainer;
}

void ReducerWorker::addData(MapperModel *data) {
	collection->push_back(data);
}

void ReducerWorker::run() {

}
