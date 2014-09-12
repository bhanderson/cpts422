#include "MemoryStream.hpp"

namespace CS422
{
	MemoryStream::MemoryStream(i64 size) {
		_buffer = new char[size];
		_length = 0;
		_size = size;
	}

	MemoryStream::~MemoryStream() {
		delete[] _buffer;
	}

	bool MemoryStream::CanRead() {
		if(_position >= _size - 1)
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
	}

	i64 MemoryStream::SetPosition(i64 position) {
		if (position >= _length)
			return _position;
		if (position < 0)
			return _position;
		_position = position;
		return _position;
	}

	int MemoryStream::Write(const void* buf, int byteCount) {
		if (_position >= _size) {
			char* new_buff = new char[_size + 64];

		}
	}

	void MemoryStream::copy_buffer(const char* old_buf, i64 old_len, char* new_buf, i64 new_len) {

	}
}