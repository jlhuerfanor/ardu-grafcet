/*
 * ParameterStore.h
 *
 *  Created on: 13/08/2017
 *      Author: leonardo
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "libtypes.h"
#define PARAM(var, len) {PTR(var), len}
#define PARAMT(var, type) {PTR(var), (uint)sizeof(type)}

typedef struct {
	ptr data;
	uint length;
} Parameter;

#endif /* PARAMETER_H_ */
