/*
 * DayParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_DAYPARSER_H_
#define COMMONS_COMMON_DAYPARSER_H_

#include <sstream>
#include <utility>
#include <cstdlib>
#include <string>
#include "common_DayModel.h"

class DayParser {
public:
	explicit DayParser();
	virtual ~DayParser();

	DayModel * parse(std::string &line);

private:
	DayParser(const DayParser&);
	DayParser& operator=(const DayParser&);
};

#endif /* COMMONS_COMMON_DAYPARSER_H_ */
