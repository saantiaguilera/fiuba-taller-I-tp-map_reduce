/*
 * DayParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <utility>
#include <string>
#include "common_MapperParser.h"

/**
 * @Public
 * @Constructor
 */
MapperParser::MapperParser() {
}

/**
 * @Public
 * @Destructor
 */
MapperParser::~MapperParser() {
}

/**
 * @Public
 * Parses a line in the form
 * (k,v) (MapperSerializer eg)
 * and builds a MapperModel
 */
MapperModel * MapperParser::parse(std::string &line) {
	std::string day, temperature, city;
	std::istringstream iss(line);

	iss >> day;
	iss >> city;
	iss >> temperature;

	std::pair<std::string, int> innerDataHolder(city,
			atoi(temperature.c_str()));

	return new MapperModel(atoi(day.c_str()), innerDataHolder);
}
