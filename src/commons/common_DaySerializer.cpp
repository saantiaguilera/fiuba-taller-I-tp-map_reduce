/*
 * DaySerializer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "common_DaySerializer.h"

DaySerializer::DaySerializer() {
}

DaySerializer::~DaySerializer() {
}

/**
 * Because the TP forces us to send in the k,v form
 * we cant reuse a same parser (because this serializing
 * is different from how the string is initially created
 * Hence, there will be 2 parsers :(
 * Long live boilerplate :D
 */
std::string DaySerializer::serialize(DayModel &dayModel) {
	//TODO Check if maybe eol is already added.
	return std::string(dayModel.first + " " + dayModel.second.first + " " + dayModel.second.first + "\n");
}
