#include "MemoryStream.hpp"

namespace CS422
{
	MemoryStream::MemoryStream(i64 size) {
		_buffer = new char[];
		_length = 0;
		_size = size;
	}

	MemoryStream::~MemoryStream() {
		delete[] _buffer;
	}

	bool MemoryStream::CanRead() {
		if(_size - 1 <= _position || 0 == _length)
			return false;
		return true;
	}

	bool MemoryStream::CanSeek() {
		if (_length == _size - 1)
			return false;
		return true;
	}

	bool MemoryStream::CanWrite() {
		return true;
	}

	i64 MemoryStream::GetLength() const {
		return _length;
	}
	
	i64 MemoryStream::GetPosition() const {
		return _position;
	}

	int MemoryStream::Read(void* buf, int byteCount) {
		if (_position >= _length)
			return 0;

		// copy into buf;
		char* read_buf = (char*)buf;
		for (int i = 0; i < byteCount; i++) {
			read_buf[i] = _buffer[_position];
			_position++;
		}
	}

	i64 MemoryStream::SetPosition(i64 position) {
		if (position >= _length || 0 > position)
			return _position;
		_position = position;
		return _position;
	}

	int MemoryStream::Write(const void* buf, int byteCount) {
		// Adjust length of buffer
		if (_position + byteCount >= _size) {
			char* new_buf = new char[_position + byteCount + 1];
			copy_buffer(_buffer, new_buf, _length);
			delete[] _buffer;
			_buffer = new_buf;
		}
		
		// Write data
		char* write_buf = (char*)buf;
		for (int i = 0; i < byteCount; i++) {
			_buffer[_position] = write_buf[i];
			_position++;

		}
	}

	void MemoryStream::copy_buffer(const char* old_buf, char* new_buf, i64 len) {
		for (int i = 0; i < len; i++) {
			new_buf[i] = old_buf[i];
		}
	}
}