#include "FileStream.hpp"

CS422::FileStream::FileStream(std::string path, std::ios_base::openmode mode){
	_buf.open(path.c_str, mode | std::ios_base::binary);
	_mode = mode | std::ios_base::binary;
}

CS422::FileStream::~FileStream(){
	_buf.close();
}

bool CS422::FileStream::CanRead(){
	return _mode & std::ios_base::in;
}

bool CS422::FileStream::CanSeek(){
	return true;
}

bool CS422::FileStream::CanWrite(){
	return _mode & std::ios_base::out;
}

void CS422::FileStream::Flush(){
	return; // it writes already, a stream is a pipe not a pit
}

i64 CS422::FileStream::GetLength() const{

	return -1;
}

i64 CS422::FileStream::GetPosition() const{
	return _buf.tellg();
}

int CS422::FileStream::Read(void *buf, int byteCount){
	_buf.read((char *) buf, byteCount);
	if (_buf.eof()) // reached the end return 0
		return 0;
	return std::strlen((char*) buf);
}

i64 CS422::FileStream::SetPosition(i64 position){
	_buf.seekg(position);
	return _buf.tellg();
}

int CS422::FileStream::Write(const void* buf, int byteCount){
	int current = _buf.tellg();
	_buf.write((char *)buf, byteCount);
	return (int)_buf.tellg() - current;
}