#include <iostream>
#include "IndexedNumberStream.hpp"

//this stream can always read
bool IndexedNumberStream::CanRead()
{
	return true;
}

//this stream can never write
bool IndexedNumberStream::CanWrite()
{

	return false;
}

//this stream can always seek
bool IndexedNumberStream::CanSeek()
{

	return true;
}

//returns the total size set at creation
i64 IndexedNumberStream::GetLength()
{
	return _size;
}

//returns currrent position
i64 IndexedNumberStream::GetPosition()
{
	return _position;
}

//returns the position module 256
unsigned int IndexedNumberStream::ProceduralGenerate()
{
	return GetPosition() % 256;
}

//reads into a buffer a set number of btyes
int IndexedNumberStream::Read(void* buf, int byteCount)
{
	unsigned char * shit = (unsigned char *)buf;
	if (byteCount > (_size - _position))
	{
		return -1;
	}
	for (int i = 0; i < byteCount; i++)
	{
		//uses the position to create the right number
		shit[i] = ProceduralGenerate();
		SetPosition(_position + 1);
	}
	shit[byteCount] = 0;
	return byteCount;
}

//checks if position is valid and sets it to it
i64 IndexedNumberStream::SetPosition(i64 position)
{
	if (position >= 0 && position < _size)
	{
		_position = position;
	}
	return _position;
}

//this stream never writes
int IndexedNumberStream::Write(const void* buf, int byteCount)
{
	return -1;
}

//creates the stream
IndexedNumberStream::IndexedNumberStream(int byteSize)
{
	_size = byteSize;
	_canRead = true;
	_canWrite = false;
	_position = 0;
}