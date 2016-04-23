/*
 * common_ReducerModel.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_REDUCERMODEL_H_
#define COMMONS_COMMON_REDUCERMODEL_H_

#include <string>
#include <utility>

//(day, (data/data/data..., temperature))
typedef std::pair<int, std::pair<std::string, int> > ReducerModel;

#endif /* COMMONS_COMMON_REDUCERMODEL_H_ */
