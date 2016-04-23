/*
 * DayFileParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_DAYFILEPARSER_H_
#define COMMONS_DAYFILEPARSER_H_

#include "DayModel.h"
#include <sstream>
#include <utility>
#include <cstdlib>
#include <string>

class DayFileParser {
public:
	explicit DayFileParser();
	virtual ~DayFileParser();

	DayModel * parse(std::string &line);

private:
	DayFileParser(const DayFileParser&);
	DayFileParser& operator=(const DayFileParser&);
};

#endif /* COMMONS_DAYFILEPARSER_H_ */
