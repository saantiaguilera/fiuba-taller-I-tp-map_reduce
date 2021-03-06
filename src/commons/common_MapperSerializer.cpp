/*
 * DaySerializer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include <string>
#include "common_MapperSerializer.h"

/**
 * @Public
 * @Constructor
 */
MapperSerializer::MapperSerializer() {
}

/**
 * @Public
 * @Destructor
 */
MapperSerializer::~MapperSerializer() {
}

/**
 * @Public
 * Because the TP forces us to send in the k,v form
 * we cant reuse a same parser (because this serializing
 * is different from how the string is initially created
 * Hence, there will be 2 parsers :(
 * Long live boilerplate :D
 *
 * I could do a BaseMapperSerializer for simplifying
 * but no time.
 */
std::string MapperSerializer::serialize(MapperModel &dayModel) {
	std::ostringstream oss;

	oss << dayModel.first << " " << dayModel.second.first << " "
			<< dayModel.second.second << "\n";

	return oss.str();
}
