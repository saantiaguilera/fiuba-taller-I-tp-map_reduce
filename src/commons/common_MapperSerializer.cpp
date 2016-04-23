/*
 * DaySerializer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "common_MapperSerializer.h"

MapperSerializer::MapperSerializer() {
}

MapperSerializer::~MapperSerializer() {
}

/**
 * Because the TP forces us to send in the k,v form
 * we cant reuse a same parser (because this serializing
 * is different from how the string is initially created
 * Hence, there will be 2 parsers :(
 * Long live boilerplate :D
 */
std::string MapperSerializer::serialize(MapperModel &dayModel) {
	//TODO Check if maybe eol is already added.
	std::ostringstream oss;

	oss << dayModel.first << " " << dayModel.second.first << " "
			<< dayModel.second.second << "\n";

	std::cout << "Serialize:: " << oss.str();

	return oss.str();
}
