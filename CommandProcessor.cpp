//============================================================================
// Name        : CommandProcessor.cpp
// Author      : Jerson Leonardo Huerfano Romero
// Version     : 1.0.1
// Copyright   : Copyright (C) 2018 Jerson Huerfano
// Description : Class for decoding and processing commands.
//============================================================================

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
		DataStream output(this->getBuffer() + this->getCount(), this->output_len);

		output.setEndianness(this->getEndianness());

		this->rseek(0);									// Reset read action
		if (this->onReceived != NULL) {

			this->onReceived(this, &output);
		}

		this->tailIndex = 0;							// reset tail counter
		this->wseek(0);									// Reset write action

		if (this->onProcessed != NULL) {
			this->onProcessed(&output);
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

uint CommandProcessor::getTailLength() const {
	return tailLength;
}

CommandProcessor::CommandProcessor(
		ptr buffer, const uint& input_len, const uint& output_len,
		const byte * tail, uint tailLength,
		CommandReceivedHandler onReceived) :
		DataStream(buffer, input_len) {
	this->tail = tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = NULL;
	this->output_len = output_len;
}

CommandProcessor::CommandProcessor(
		ptr buffer, const uint& input_len, const uint& output_len,
		const char * tail, uint tailLength,
		CommandReceivedHandler onReceived) :
		DataStream(buffer, input_len) {
	this->tail = (const byte*) tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = NULL;
	this->output_len = output_len;
}

CommandProcessor::CommandProcessor(
		ptr buffer, const uint& input_len, const uint& output_len,
		const byte* tail, uint tailLength, CommandReceivedHandler onReceived,
		CommandProcessedHandler onProcessed) :
		DataStream(buffer, input_len) {
	this->tail = tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = onProcessed;
	this->output_len = output_len;
}

CommandProcessor::CommandProcessor(
		ptr buffer, const uint& input_len, const uint& output_len,
		const char* tail, uint tailLength,
		CommandReceivedHandler onReceived,
		CommandProcessedHandler onProcessed) :
		DataStream(buffer, input_len) {
	this->tail = (const byte*) tail;
	this->tailIndex = 0;
	this->tailLength = tailLength;
	this->onReceived = onReceived;
	this->onProcessed = onProcessed;
	this->output_len = output_len;
}
