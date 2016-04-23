/*
 * DayFileParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <utility>
#include <string>
#include "common_MapperFileParser.h"

/**
 * @Public
 * @Constructor
 */
MapperFileParser::MapperFileParser() {
}

/**
 * @Public
 * @Destructor
 */
MapperFileParser::~MapperFileParser() {
}

/**
 * @Public
 * Parses a line in the form of
 * "data temperature day" and builds
 * a MapperModel from it
 */
MapperModel * MapperFileParser::parse(std::string &line) {
	std::string day, temperature, city;
	std::istringstream iss(line);

	iss >> city;
	iss >> temperature;
	iss >> day;

	std::pair<std::string, int> innerDataHolder(city,
			atoi(temperature.c_str()));

	return new MapperModel(atoi(day.c_str()), innerDataHolder);
}
