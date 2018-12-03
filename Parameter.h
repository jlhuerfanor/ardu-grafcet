//============================================================================
// Name        : Parameters.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Container for a memory parameter.
//============================================================================


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
