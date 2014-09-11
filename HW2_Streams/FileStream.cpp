#include "FileStream.hpp"

CS422::FileStream::FileStream(std::string path, std::ios_base::openmode mode)
	: _buf(path, mode){
}

CS422::FileStream::~FileStream(){
	_buf.close();
}

bool CS422::FileStream::CanRead(){
	return _readable;
}

bool CS422::FileStream::CanSeek(){
	return _seekable;
}

bool CS422::FileStream::CanWrite(){
	return _writable;
}

void CS422::FileStream::Flush(){
	return;
}

i64 CS422::FileStream::GetLength(){
	return _buf.end - _buf.beg;
}

i64 CS422::FileStream::GetPosition(){
	return _buf.tellg();
}

int CS422::FileStream::Read(void *buf, int byteCount){
	_buf.read((char *) buf, byteCount);
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