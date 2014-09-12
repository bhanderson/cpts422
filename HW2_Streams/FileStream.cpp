#include "FileStream.hpp"
// create the stream
CS422::FileStream::FileStream(std::string path, std::ios::openmode mode){
	_buf.open(path.c_str(), mode | std::ios::binary);
	_mode = mode | std::ios::binary;
}
// close the stream
CS422::FileStream::~FileStream(){
	_buf.close();
}
// check if the stream is readable
bool CS422::FileStream::CanRead(){
	return _mode & std::ios::in;
}
// a filesteram is always seekable
bool CS422::FileStream::CanSeek(){
	return true;
}
// check if the stream is writeable
bool CS422::FileStream::CanWrite(){
	return _mode && std::ios::out;
}
// flush the stream to disk
void CS422::FileStream::Flush(){
	_buf.flush();
}
// get the size of the stream
i64 CS422::FileStream::GetLength(){
	std::streampos current = _buf.tellg();
	int length = _buf.seekg(0, _buf.end).tellg();
	_buf.seekg(current);
	return length;
}
// basic get stream position
i64 CS422::FileStream::GetPosition(){
	return _buf.tellg();
}
// read num bytes of the stream, if the read reaches the end the clear function
// is used to clear the fail bit
int CS422::FileStream::Read(void *buf, int byteCount){
	int length = _buf.read((char *) buf, byteCount).gcount();
	_buf.clear();
	return length;
}
// set the position in the stream using seekg from fstream
// if the position is larger then the length then return position
i64 CS422::FileStream::SetPosition(i64 position){
	if (!CanSeek())
		return -1;
	if (GetLength() < position)
		return GetPosition();
	_buf.seekg(position);
	return GetPosition();
}
// write to the stream and return the lenght of what was just wrote
int CS422::FileStream::Write(const void* buf, int byteCount){
	if (CanWrite()) {
		std::streampos current = GetPosition();
		_buf.write((const char *) buf, byteCount);
		return _buf.tellg() - current;
	}
	return 0;
}
