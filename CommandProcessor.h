/*
 * CommandProcessor.h
 *
 *  Created on: 11/08/2017
 *      Author: leonardo
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include "DataStream.h"

typedef void (*CommandAction)(DataStream *, uint);

class CommandProcessor: public DataStream {
protected:
	const byte * tail;
	uint tailLength; uint tailIndex;
	CommandAction action;
	void _encode(const byte& data);
	bool _encode(const ptr data, const uint & length, const byte& encoding);
public:
	CommandProcessor(ptr buffer, uint length, const byte * tail, uint tailLength, CommandAction action);
	CommandProcessor(ptr buffer, uint length, const char * tail, uint tailLength, CommandAction action);

	CommandAction getAction() const;
	const byte* getTail() const;
	uint getTailIndex() const;
	uint getTailLength() const;
};

#endif /* COMMANDPROCESSOR_H_ */
