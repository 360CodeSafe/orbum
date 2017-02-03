#pragma once

#include <queue>

#include "Common/Global/Globals.h"

/*
Represents a FIFO queue used in (for example) the EE/IOP DMAC channels.
The minimum sized data unit that can be read/written to the queue is 32-bit, however 128-bit read/writes are also allowed.
TODO: test perf (use std::queue or own?), add in thread safety.
*/
class FIFOQueue_t
{
public:
	explicit FIFOQueue_t(const size_t & maxSize);
	explicit FIFOQueue_t(const char * mnemonic, const size_t & maxSize);
	virtual ~FIFOQueue_t();

	/*
	Read 32-bits of data out of the FIFO queue, and removes it.
	*/
	virtual u32 readWord(const Context & context);

	/*
	Read 128-bits of data out of the FIFO queue, and remove them (uses 4 x 32-bit reads stored in a u128).
	*/
	virtual u128 readQword(const Context & context);

	/*
	Writes 32-bits of data to the FIFO queue.
	*/
	virtual void writeWord(const Context & context, const u32 & data);

	/*
	Write 128-bits of data to the FIFO queue (splits the u128 into 4 x 32-bit).
	*/
	virtual void writeQword(const Context & context, const u128 & data);

	/*
	Returns if the FIFO queue has no data available.
	*/
	bool isEmpty() const;

	/*
	Returns if the FIFO queue is full.
	*/
	bool isFull() const;

	/*
	Gets the current number of 32-bit data elements in the queue.
	*/
	size_t getCurrentSize() const;

	/*
	Gets the max allowable number of 32-bit data elements this FIFO queue can hold.
	*/
	size_t getMaxSize() const;

	/*
	Gets the mnemonic of this register. Used for debug/logging.
	*/
	const char * getMnemonic() const;

private:
	/*
	The mnemonic.
	*/
	const std::string mMnemonic;

	/*
	The max number of 32-bit data elements allowed in the queue, set to the constructor paramter.
	*/
	size_t mMaxSize;

	/*
	The backend for the FIFO queue.
	*/
	std::queue<u32> mFIFOQueue;
};

