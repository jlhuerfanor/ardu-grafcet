//============================================================================
// Name        : DataStream.h
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Endianness-independent bytestream.
//============================================================================

#ifndef DATASTREAM_H_
#define DATASTREAM_H_

#include "libtypes.h"
#include "Parameter.h"
#include <string.h>

#ifndef ARDUINO
#include <cstddef>
#endif

#define L_ENDIAN 'L'
#define B_ENDIAN 'B'

extern byte * DATASTREAM_EOL;

class DataStream {
protected:
	ptr buffer;
	uint count;
	uint writeCursor;
	uint readCursor;
	byte encoding;

	virtual void _encode(const byte& data);
	virtual bool _encode(const ptr data, const uint & length, const byte& encoding);
	virtual bool _decode(ptr data, const uint & length, const byte& encoding);
public:
	DataStream(ptr buffer, uint count);
	DataStream(ptr buffer, uint count, byte encoding);
	virtual ~DataStream();

	void wseek(const uint & position);

	virtual bool encode(const ptr data, const uint & length);
	bool encode(const char * data, const uint & length);
	bool encode(const ushort & data);
	bool encode(const uint & data);
	bool encode(const ulong & data);
	bool encode(const short & data);
	bool encode(const int & data);
	bool encode(const long & data);
	bool encode(const byte & data);
	bool encode(const char & data);
	bool encode(const float & data);
	bool encode(const double & data);
	bool encode(const bool & data);
	bool encode(const Parameter& parameter);
	bool encode(const char* str);

	void rseek(const uint & position);
	bool decode(ptr data, const uint & length);
	bool decode(char * data, const uint & length);
	bool decode(ushort & data);
	bool decode(uint & data);
	bool decode(ulong & data);
	bool decode(short & data);
	bool decode(int & data);
	bool decode(long & data);
	bool decode(byte & data);
	bool decode(char & data);
	bool decode(float & data);
	bool decode(double & data);
	bool decode(bool & data);
	bool decode(Parameter& parameter);

	ptr getBuffer() const;
	uint getCount() const;
	uint getReadCursor() const;
	uint getWriteCursor() const;

	static byte endianness();
	byte getEndianness() const;
	void setEndianness(byte endianness);
};

#endif /* DATASTREAM_H_ */
