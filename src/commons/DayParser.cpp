/*
 * DayParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "DayParser.h"

DayParser::DayParser() {
}

DayParser::~DayParser() {
}

DayModel * DayParser::parse(std::string &line) {
	std::string day, temperature, city;
	std::istringstream iss(line);

	iss >> day;
	iss >> city;
	iss >> temperature;

	std::pair<std::string, int> innerDataHolder(city, atoi(temperature.c_str()));

	return new DayModel(atoi(day.c_str()), innerDataHolder);
}
