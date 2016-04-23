/*
 * DayFileParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "common_MapperFileParser.h"

MapperFileParser::MapperFileParser() {
}

MapperFileParser::~MapperFileParser() {
}

MapperModel * MapperFileParser::parse(std::string &line) {
	std::string day, temperature, city;
	std::istringstream iss(line);

	iss >> city;
	iss >> temperature;
	iss >> day;

	std::pair<std::string, int> innerDataHolder(city, atoi(temperature.c_str()));

	return new MapperModel(atoi(day.c_str()), innerDataHolder);
}
