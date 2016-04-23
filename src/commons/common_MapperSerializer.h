/*
 * DaySerializer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_MAPPERSERIALIZER_H_
#define COMMONS_COMMON_MAPPERSERIALIZER_H_

#include <string>

#include "common_MapperModel.h"

class MapperSerializer {
public:
	explicit MapperSerializer();
	virtual ~MapperSerializer();

	std::string serialize(MapperModel &dayModel);

private:
	MapperSerializer(const MapperSerializer&);
	MapperSerializer& operator=(const MapperSerializer&);
};

#endif /* COMMONS_COMMON_MAPPERSERIALIZER_H_ */
