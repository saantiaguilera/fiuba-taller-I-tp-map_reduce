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
	for (std::list<MapperModel*>::iterator it = collection->begin();
			it != collection->end(); ++it) {
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
	std::list<std::string> cities;
	std::string citiesToString;
	int hottestTemperature = -273; //Use absolute zero as init value
	int day = -1;

	for (std::list<MapperModel*>::iterator it = collection->begin();
			it != collection->end(); ++it) {
		if (day == -1)
			day = (*it)->first;

		if ((*it)->second.second > hottestTemperature) {
			//Its higher, clear cities list, add this one and update temp
			cities.clear();
			cities.push_back((*it)->second.first);

			hottestTemperature = (*it)->second.second;
		} else if ((*it)->second.second == hottestTemperature) {
			//Theres another city with max. Add it
			cities.push_back((*it)->second.first);
		}
	}

	//On done. Update the reducer model
	cities.sort();

	//To string.
	std::list<std::string>::iterator end = cities.end();
	for (std::list<std::string>::iterator it = cities.begin(); it != end;) {
		citiesToString.append((*it));

		if (++it != end)
			citiesToString.append("/");
	}

	//Update the model
	*resultContainer = std::pair<int, std::pair<std::string, int> >(
			day,
			std::pair<std::string, int>(citiesToString, hottestTemperature));
}
