/*
 * DayModel.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_MAPPERMODEL_H_
#define COMMONS_COMMON_MAPPERMODEL_H_

#include <string>
#include <utility>

//(day, (city, temperature))
typedef std::pair<int, std::pair<std::string, int> > MapperModel;

#endif /* COMMONS_COMMON_MAPPERMODEL_H_ */
