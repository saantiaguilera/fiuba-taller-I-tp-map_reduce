/*
 * DayParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "common_MapperParser.h"

MapperParser::MapperParser() {
}

MapperParser::~MapperParser() {
}

MapperModel * MapperParser::parse(std::string &line) {
	std::string day, temperature, city;
	std::istringstream iss(line);

	iss >> day;
	iss >> city;
	iss >> temperature;

	std::pair<std::string, int> innerDataHolder(city, atoi(temperature.c_str()));

	return new MapperModel(atoi(day.c_str()), innerDataHolder);
}
