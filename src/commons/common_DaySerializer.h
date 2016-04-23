/*
 * DaySerializer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_COMMON_DAYSERIALIZER_H_
#define COMMONS_COMMON_DAYSERIALIZER_H_

#include <string>
#include "common_DayModel.h"

class DaySerializer {
public:
	explicit DaySerializer();
	virtual ~DaySerializer();

	std::string serialize(DayModel &dayModel);

private:
	DaySerializer(const DaySerializer&);
	DaySerializer& operator=(const DaySerializer&);
};

#endif /* COMMONS_COMMON_DAYSERIALIZER_H_ */
