/*
 * server_ReducerComparator.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: santiago
 */

#include "server_ReducerComparator.h"

/**
 * @Public
 * @Constructor
 */
ReducerComparator::ReducerComparator() {
}

/**
 * @Public
 * @Destructor
 */
ReducerComparator::~ReducerComparator() {
}

/**
 * @Public
 * @Static
 * @note: Sorts two reducer models by
 * day ASC
 */
bool ReducerComparator::compare(ReducerModel *lrm, ReducerModel *rrm) {
	return (lrm->first < rrm->first);
}
