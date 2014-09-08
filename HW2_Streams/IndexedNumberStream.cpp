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


i64 IndexedNumberStream::GetLength() const
{
	return _size;
}

i64 IndexedNumberStream::GetPosition() const
{
	return _position;
}

int IndexedNumberStream::Read(void* buf, int byteCount)
{
	if (byteCount > (_size - _position))
	{
		return -1;
	}
	unsigned char* tempBuf = new unsigned char[byteCount];
	for (int i = 0; i < byteCount; i++)
	{
		tempBuf[i] = '0';
	}
	buf = tempBuf;
	SetPosition((_position + byteCount));
	return byteCount;
}

i64 IndexedNumberStream::SetPosition(i64 position)
{
	if (position> 0 && position > _size)
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
}