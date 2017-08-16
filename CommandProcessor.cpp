/*
 * CommandProcessor.cpp
 *
 *  Created on: 11/08/2017
 *      Author: leonardo
 */

#include "CommandProcessor.h"

CommandAction CommandProcessor::getAction() const {
	return action;
}

const byte* CommandProcessor::getTail() const {
	return tail;
}

uint CommandProcessor::getTailIndex() const {
	return tailIndex;
}

void CommandProcessor::_encode(const byte& data) {
	DataStream::_encode(data);

	tailIndex = (data == this->tail[tailIndex])? tailIndex + 1 : 0;

	if(this->tailIndex == this->tailLength)
	{
		this->rseek(0);									// Reset read action
		this->action(this, this->getWriteCursor());		// Calls command action
		this->tailIndex = 0;							// reset tail counter
		this->wseek(0);									// Reset write action
	}
}

bool CommandProcessor::_encode(const ptr data, const uint& length,
		const byte& encoding) {
	bool result = DataStream::_encode(data, length, encoding);

	if(!result) this->wseek(0);

	return result;
}

uint CommandProcessor::getTailLength() const {
	return tailLength;
}

CommandProcessor::CommandProcessor(
		ptr buffer,
		uint length,
		const byte * tail,
		uint tailLength,
		CommandAction action) : DataStream(buffer, length) {
	this->tail = tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->action = action;
}

CommandProcessor::CommandProcessor(
		ptr buffer,
		uint length,
		const char * tail,
		uint tailLength,
		CommandAction action) : DataStream(buffer, length) {
	this->tail = (const byte*)tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->action = action;
}
