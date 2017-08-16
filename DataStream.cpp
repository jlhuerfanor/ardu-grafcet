/*
 * UdpPacket.cpp
 *
 *  Created on: 11/08/2017
 *      Author: leonardo
 */

#include "DataStream.h"

int endiannessFlag = 1;

DataStream::DataStream(ptr buffer, uint count) {
	// TODO Auto-generated constructor stub
	this->buffer = buffer;
	this->count = count;
	this->readCursor = 0;
	this->writeCursor = 0;
	this->encoding = DataStream::endianness();
}

DataStream::DataStream(ptr buffer, uint count, byte encoding) {
	this->buffer = buffer;
	this->count = count;
	this->readCursor = 0;
	this->writeCursor = 0;
	this->encoding = ((encoding == L_ENDIAN) || (encoding == B_ENDIAN))? encoding : DataStream::endianness();
}

ptr DataStream::getBuffer() const {
	return buffer;
}

uint DataStream::getCount() const {
	return count;
}

uint DataStream::getReadCursor() const {
	return readCursor;
}

void DataStream::wseek(const uint& position) {
	this->writeCursor = position;
}

void DataStream::_encode(const byte& data)
{
	this->buffer[this->getWriteCursor()] = data;
	this->writeCursor += 1;
}
bool DataStream::_encode(const ptr data, const uint& length,
		const byte& encoding) {
	if (this->count >= this->getWriteCursor() + length) {

		bool reverse = (endianness() == L_ENDIAN && encoding == B_ENDIAN)
				|| (endianness() == B_ENDIAN && encoding == L_ENDIAN);

		for (uint i = 0; i < length; i++)
			this->_encode(data[((reverse) ? length - i - 1 : i)]);

		return true;
	} else
		return false;
}

bool DataStream::encode(const ptr data, const uint & length) {
	return this->_encode(data, length, this->encoding);
}

bool DataStream::encode(const ushort& data) {
	return encode((const ptr) (&data), sizeof(ushort));
}

bool DataStream::encode(const uint& data) {
	return encode((const ptr) (&data), sizeof(uint));
}

bool DataStream::encode(const ulong& data) {
	return encode((const ptr) (&data), sizeof(ulong));
}

bool DataStream::encode(const short & data) {
	return encode((const ptr) (&data), sizeof(short));
}

bool DataStream::encode(const int& data) {
	return encode((const ptr) (&data), sizeof(int));
}

bool DataStream::encode(const long & data) {
	return encode((const ptr) (&data), sizeof(long));
}

bool DataStream::encode(const byte& data) {
	return _encode((const ptr) (&data), sizeof(byte), endianness());
}

bool DataStream::encode(const char& data) {
	return encode((const ptr) (&data), sizeof(char));
}

bool DataStream::encode(const float& data) {
	return encode((const ptr) (&data), sizeof(float));
}

bool DataStream::encode(const double& data) {
	return encode((const ptr) (&data), sizeof(double));
}

bool DataStream::encode(const bool& data) {
	return encode((const ptr) (&data), sizeof(bool));
}

bool DataStream::encode(const char* data, const uint& length) {
	// Use the system endianness when encoding strings, cause
	// system treats it as byte array.
	return _encode((const ptr) data, length, endianness());
}

bool DataStream::encode(const Parameter& parameter) {
	return _encode(parameter.data, parameter.length, this->encoding);
}

void DataStream::rseek(const uint& position) {
	this->readCursor = position;
}

bool DataStream::_decode(ptr data, const uint& length, const byte& encoding) {
	if (this->count >= this->getReadCursor() + length) {
		bool reverse = (endianness() == L_ENDIAN && encoding == B_ENDIAN)
				|| (endianness() == B_ENDIAN && encoding == L_ENDIAN);

		for (uint i = 0; i < length; i++)
			data[((reverse) ? length - i - 1 : i)] =
					this->buffer[this->getReadCursor() + i];
		this->readCursor += length;
		return true;
	} else
		return false;
}

bool DataStream::decode(ptr data, const uint & length) {
	return this->_decode(data, length, this->encoding);
}

bool DataStream::decode(ushort& data) {
	return decode((ptr) (&data), sizeof(ushort));
}

bool DataStream::decode(uint& data) {
	return decode((ptr) (&data), sizeof(uint));
}

bool DataStream::decode(ulong& data) {
	return decode((ptr) (&data), sizeof(ulong));
}

bool DataStream::decode(short & data) {
	return decode((ptr) (&data), sizeof(short));
}

bool DataStream::decode(int& data) {
	return decode((ptr) (&data), sizeof(int));
}

bool DataStream::decode(long & data) {
	return decode((ptr) (&data), sizeof(long));
}

bool DataStream::decode(byte& data) {
	return _decode((ptr) (&data), sizeof(byte), endianness());
}

bool DataStream::decode(char& data) {
	return decode((ptr) (&data), sizeof(char));
}

bool DataStream::decode(float& data) {
	return decode((ptr) (&data), sizeof(float));
}

bool DataStream::decode(double& data) {
	return decode((ptr) (&data), sizeof(double));
}

bool DataStream::decode(char* data, const uint& length) {
	return _decode((ptr) data, length, endianness());
}

bool DataStream::decode(bool& data) {
	return decode((ptr) (&data), sizeof(bool));
}

bool DataStream::decode(Parameter& parameter) {
	return decode(parameter.data, parameter.length);
}

byte DataStream::getEndianness() const {
	return encoding;
}

void DataStream::setEndianness(byte endianness) {
	this->encoding = ((endianness == L_ENDIAN) || (endianness == B_ENDIAN)) ? endianness : DataStream::endianness();
}

uint DataStream::getWriteCursor() const {
	return writeCursor;
}

DataStream::~DataStream() {
}

byte DataStream::endianness() {
	if (*((ptr) &endiannessFlag) == 1)
		return L_ENDIAN;
	else
		return B_ENDIAN;
}
