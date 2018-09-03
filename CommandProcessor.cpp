/*
 * CommandProcessor.cpp
 *
 *  Created on: 11/08/2017
 *      Author: leonardo
 */

#include "CommandProcessor.h"

const byte* CommandProcessor::getTail() const {
	return tail;
}

uint CommandProcessor::getTailIndex() const {
	return tailIndex;
}

void CommandProcessor::_encode(const byte& data) {
	DataStream::_encode(data);

	tailIndex = (data == this->tail[tailIndex]) ? tailIndex + 1 : 0;

	if (this->tailIndex == this->tailLength) {
		this->rseek(0);									// Reset read action
		if (this->onReceived != NULL) {
			this->onReceived(this, this->getOutput());
		}

		this->tailIndex = 0;							// reset tail counter
		this->wseek(0);									// Reset write action

		if (this->onProcessed != NULL) {
			this->onProcessed(this->getOutput());
		}
	}
}

bool CommandProcessor::_encode(const ptr data, const uint& length,
		const byte& encoding) {
	bool result = DataStream::_encode(data, length, encoding);

	if (!result)
		this->wseek(0);

	return result;
}

DataStream* CommandProcessor::getOutput() {
	return output;
}

CommandProcessedHandler CommandProcessor::getOnProcessed() const {
	return onProcessed;
}

void CommandProcessor::setOnProcessed(CommandProcessedHandler onProcessed) {
	this->onProcessed = onProcessed;
}

CommandReceivedHandler CommandProcessor::getOnReceived() const {
	return onReceived;
}

void CommandProcessor::setOnReceived(CommandReceivedHandler onReceived) {
	this->onReceived = onReceived;
}

void CommandProcessor::setOutput(DataStream* output) {
	this->output = output;
}

uint CommandProcessor::getTailLength() const {
	return tailLength;
}

CommandProcessor::CommandProcessor(ptr buffer, uint length, const byte * tail,
		uint tailLength, CommandReceivedHandler onReceived) :
		DataStream(buffer, length) {
	this->tail = tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = NULL;
	this->output = NULL;
}

CommandProcessor::CommandProcessor(ptr buffer, uint length, const char * tail,
		uint tailLength, CommandReceivedHandler onReceived) :
		DataStream(buffer, length) {
	this->tail = (const byte*) tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = NULL;
	this->output = NULL;
}
