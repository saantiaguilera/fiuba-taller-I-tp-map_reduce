/*
 * server_ReducerComparator.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "server_ReducerComparator.h"

ReducerComparator::ReducerComparator() {
}

ReducerComparator::~ReducerComparator() {
}

bool ReducerComparator::compare(ReducerModel *lrm, ReducerModel *rrm) {
	return (lrm->first < rrm->first);
}
