#include <iostream>
#include "IndexedNumberStream.hpp"

bool IndexedNumberStream::CanRead()
{
	return true;
}

bool IndexedNumberStream::CanWrite()
{

	return false;
}

bool IndexedNumberStream::CanSeek()
{

	return true;
}


i64 IndexedNumberStream::GetLength()
{
	return _size;
}

i64 IndexedNumberStream::GetPosition()
{
	return _position;
}

unsigned int IndexedNumberStream::ProceduralGenerate()
{
	return GetPosition() % 256;
}

int IndexedNumberStream::Read(void* buf, int byteCount)
{
	unsigned char * shit = (unsigned char *)buf;
	if (byteCount > (_size - _position))
	{
		return -1;
	}
	for (int i = 0; i < byteCount; i++)
	{
		shit[i] = ProceduralGenerate();
		SetPosition(_position + 1);
	}
	shit[byteCount] = 0;
	return byteCount;
}

i64 IndexedNumberStream::SetPosition(i64 position)
{
	if (position >= 0 && position < _size)
	{
		_position = position;
	}
	return _position;
}

int IndexedNumberStream::Write(const void* buf, int byteCount)
{
	return -1;
}

IndexedNumberStream::IndexedNumberStream(int byteSize)
{
	_size = byteSize;
	_canRead = true;
	_canWrite = false;
	_position = 0;
}