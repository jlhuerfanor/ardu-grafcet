//============================================================================
// Name        : libtypes.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : some type definitions.
//============================================================================

#ifndef LIBTYPES_H_
#define LIBTYPES_H_

#ifndef ARDUINO
typedef unsigned char byte;
#else
#include <Arduino.h>
#endif
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef byte * ptr;


#define ULONG_MAX ((ulong)0xFFFF)
#define LONG_MAX ((long)0xFFFF)
#define PTR(a) ((ptr)(&(a)))
#define BIT(n) (1 << n)

#endif /* LIBTYPES_H_ */
