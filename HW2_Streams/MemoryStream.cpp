#include "MemoryStream.hpp"
#include <string>

namespace CS422
{
	MemoryStream::MemoryStream(i64 size) {
		_buffer = new u8[size];
		_position = 0;
		_size = size;
	}

	MemoryStream::~MemoryStream() {
		delete[] _buffer;
	}

	bool MemoryStream::CanRead() {
		return true; // can always read but read could be 0
		// Cannot read off end of stream
		if(_size <= _position || 0 == _size)
			return false;
		return true;
	}

	bool MemoryStream::CanSeek() {
		return true; // can seek in size of 0 but only to 0
		// Cannot seek in empty stream
		if (0 == _size)
			return false;
		return true;
	}

	bool MemoryStream::CanWrite() {
		return true;
	}

	i64 MemoryStream::GetLength() {
		return _size;
	}
	
	i64 MemoryStream::GetPosition() {
		return _position;
	}

	int MemoryStream::Read(void* buf, int byteCount) {
		i64 bytes = 0;

		if (_position == _size - 1)
			return 0;
		if (byteCount > _size - _position)
			bytes = _size - _position;
		else
			bytes = byteCount;
		memcpy(buf, _buffer + _position, bytes);
		return bytes;
		/*
		// Cant read beyond length of the stream.
		if (_position >= _size)
			return 0;

		// copy into buf;
		char* read_buf = (char*)buf;
		int i;
		for (i = 0; i < byteCount && i < _size; i++) {
			read_buf[i] = _buffer[_position];
			_position++;
		}
		return i;
		*/
	}

	i64 MemoryStream::SetPosition(i64 position) {
		if (_size - 1 < position || position < 0)
			return _position;
		_position = position;
		return _position;
		/*
		// Cannot seek beyond the length of the stream.
		// Positions are positive.
		if (position >= _size || 0 > position)
			return _position;
		_position = position;
		return _position;
		*/
	}

	int MemoryStream::Write(const void* buf, int byteCount) {
		u8 *newbuf = (u8 *) realloc(_buffer, _size + byteCount);
		if (newbuf == NULL)
			return -1;
		_buffer = newbuf;
		memcpy(_buffer + _position, buf, byteCount);

		if ((_position + byteCount) > _size)
			_size = _position + byteCount;
		_position += byteCount;
		return byteCount;
		/*

		// Adjust length of buffer
		if (_position + byteCount >= _size) {
			char* new_buf = new char[_position + byteCount + 1];
			copy_buffer(_buffer, new_buf, _size);
			delete[] _buffer;
			_buffer = new_buf;
			_size = _position + byteCount + 1;
		}
		
		// Write data
		char* write_buf = (char*)buf;
		int i;
		for (i = 0; i < byteCount; i++) {
			_buffer[_position] = write_buf[i];
			_position++;
		}
		_size = _position + 1;
		return i + 1;
		*/
	}

	void MemoryStream::copy_buffer(const char* old_buf, char* new_buf, i64 len) {
		for (int i = 0; i < len; i++) {
			new_buf[i] = old_buf[i];
		}
	}
}