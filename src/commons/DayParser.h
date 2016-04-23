/*
 * DayParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_DAYPARSER_H_
#define COMMONS_DAYPARSER_H_

#include "DayModel.h"
#include <sstream>
#include <utility>
#include <cstdlib>
#include <string>

class DayParser {
public:
	explicit DayParser();
	virtual ~DayParser();

	DayModel * parse(std::string &line);

private:
	DayParser(const DayParser&);
	DayParser& operator=(const DayParser&);
};

#endif /* COMMONS_DAYPARSER_H_ */
