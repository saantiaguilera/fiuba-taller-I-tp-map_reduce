/*
 * DaySerializer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef COMMONS_DAYSERIALIZER_H_
#define COMMONS_DAYSERIALIZER_H_

#include "DayModel.h"
#include <string>

class DaySerializer {
public:
	explicit DaySerializer();
	virtual ~DaySerializer();

	std::string serialize(DayModel &dayModel);

private:
	DaySerializer(const DaySerializer&);
	DaySerializer& operator=(const DaySerializer&);
};

#endif /* COMMONS_DAYSERIALIZER_H_ */
