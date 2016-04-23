/*
 * server_ReducerComparator.h
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#ifndef SERVER_MISC_SERVER_REDUCERCOMPARATOR_H_
#define SERVER_MISC_SERVER_REDUCERCOMPARATOR_H_

#include "../../commons/common_ReducerModel.h"

/**
 * Comparator class for sorting
 * reducer models
 */
class ReducerComparator {
public:
	ReducerComparator();
	virtual ~ReducerComparator();

	static bool compare(ReducerModel * lrm, ReducerModel * rrm);

private:
	ReducerComparator(const ReducerComparator&);
	ReducerComparator& operator=(const ReducerComparator&);
};

#endif /* SERVER_MISC_SERVER_REDUCERCOMPARATOR_H_ */
