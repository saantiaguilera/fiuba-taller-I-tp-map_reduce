/*
 * DayFileParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_MAPPERFILEPARSER_H_
#define COMMONS_COMMON_MAPPERFILEPARSER_H_

#include <sstream>
#include <utility>
#include <cstdlib>
#include <string>

#include "common_MapperModel.h"

class MapperFileParser {
public:
	explicit MapperFileParser();
	virtual ~MapperFileParser();

	MapperModel * parse(std::string &line);

private:
	MapperFileParser(const MapperFileParser&);
	MapperFileParser& operator=(const MapperFileParser&);
};

#endif /* COMMONS_COMMON_MAPPERFILEPARSER_H_ */
