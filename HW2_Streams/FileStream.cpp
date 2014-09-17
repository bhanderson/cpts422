#include "FileStream.hpp"

CS422::FileStream::FileStream(std::string path, std::ios::openmode mode){
	_buf.open(path.c_str(), mode | std::ios::binary);
	_mode = mode | std::ios::binary;
}

CS422::FileStream::~FileStream(){
	_buf.close();
}

bool CS422::FileStream::CanRead(){
	return _mode & std::ios::in;
}

bool CS422::FileStream::CanSeek(){
	return true;
}

bool CS422::FileStream::CanWrite(){
	return _mode && std::ios::out;
}

void CS422::FileStream::Flush(){
	_buf.flush();
}

i64 CS422::FileStream::GetLength(){
	std::streampos current = _buf.tellg();
	int length = _buf.seekg(0, _buf.end).tellg();
	_buf.seekg(current);
	return length;
}

i64 CS422::FileStream::GetPosition(){
	return _buf.tellg();
}

int CS422::FileStream::Read(void *buf, int byteCount){
	int length = _buf.read((char *) buf, byteCount).gcount();
	_buf.clear();
	return length;
}

i64 CS422::FileStream::SetPosition(i64 position){
	if (!CanSeek())
		return -1;
	if (GetLength() < position)
		return GetPosition();
	_buf.seekg(position);
	return GetPosition();
}

int CS422::FileStream::Write(const void* buf, int byteCount){
	if (CanWrite()) {
		std::streampos current = GetPosition();
		_buf.write((const char *) buf, byteCount);
		return _buf.tellg() - current;
	}
	return 0;
}