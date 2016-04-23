/*
 * server_SocketReducerWorker.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <utility>
#include <string>
#include <list>
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

/**
 * @Private
 *
 * Attach the variable were we will be
 * posting our results.
 * It should be locked when r/w but
 * since we are the only ones using
 * it (server will start using them
 * after we are joined), its alread
 * threadsafe.
 */
void ReducerWorker::attachResultContainer(ReducerModel *resultContainer) {
	this->resultContainer = resultContainer;
}

/**
 * @Private
 * Append to the data list a data
 */
void ReducerWorker::addData(MapperModel *data) {
	collection->push_back(data);
}

/**
 * @Protected
 * @Runnable of the thread.
 */
void ReducerWorker::run() {
	//Init local vars
	std::string citiesToString;
	std::list<std::string> cities;
	int hottestTemperature = -273; //Use absolute zero as init value
	int day = -1;

	for (std::list<MapperModel*>::iterator it = collection->begin();
			it != collection->end(); ++it) {
		//Set the day if not setted already
		if (day == -1)
			day = (*it)->first;

		/**
		 * If the temp of this data is higher
		 * than the current hottest one,
		 * clear the history of that temperature
		 * and use this one
		 */
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
	//Sort the cities alphabetically (case-sensitive)
	cities.sort();

	//To string.
	std::list<std::string>::iterator end = cities.end();
	for (std::list<std::string>::iterator it = cities.begin(); it != end;) {
		citiesToString.append((*it));

		if (++it != end)
			citiesToString.append("/");
	}

	//Update the model
	*resultContainer = std::pair<int, std::pair<std::string, int> >(day,
			std::pair<std::string, int>(citiesToString, hottestTemperature));
}
