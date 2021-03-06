/*
 * DayParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_MAPPERPARSER_H_
#define COMMONS_COMMON_MAPPERPARSER_H_

#include <sstream>
#include <utility>
#include <cstdlib>
#include <string>

#include "common_MapperModel.h"

/**
 * Default class for parsing a string
 * and build a MapperModel
 * string should be serialized in form
 * (k,v)
 */
class MapperParser {
public:
	MapperParser();
	virtual ~MapperParser();

	MapperModel * parse(std::string &line);

private:
	MapperParser(const MapperParser&);
	MapperParser& operator=(const MapperParser&);
};

#endif /* COMMONS_COMMON_MAPPERPARSER_H_ */
