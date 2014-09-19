#include "FileStream.hpp"
// create the stream
CS422::FileStream::FileStream(std::string path, std::ios::openmode mode){
	_pos = 0;
	_size = 0;
	_path = path;
	_mode = mode | std::ios::binary;
	_buf = NULL;
	// check if the file exists
	std::ifstream f(path.c_str(), _mode | std::ios::ate);
	if (f.good()){
		_size = (int)f.tellg();
		f.seekg(0);
		_buf = (u8 *) malloc(sizeof(char)*_size);
		if (_buf == NULL)
			exit(1);
		f.read((char *)_buf, _size);
	}
	f.close();
}
// close the stream
CS422::FileStream::~FileStream(){
	Flush();
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
	return _mode & std::ios::out;
}
// flush the stream to disk
void CS422::FileStream::Flush(){
	if (!CanWrite() || _size == 0 || _buf == NULL)
		return;
	std::ofstream f;
	f.open(_path.c_str(), _mode);
	f.seekp(_pos);
	f.write((char *) _buf, _size);
	f.close();
	free(_buf);
	_buf = NULL;
	_pos = 0;
	_size = 0;
}
// get the size of the stream
i64 CS422::FileStream::GetLength(){
	return _size;
}
// basic get stream position
i64 CS422::FileStream::GetPosition(){
	return _pos;
}

int CS422::FileStream::Read(void *buf, int byteCount){
	i64 bytes = 0;
	if (_buf == NULL || !CanRead())
		return -1;
	if (_pos == _size - 1)
		return 0;
	if (byteCount > _size - _pos)
		bytes = _size - _pos;
	else
		bytes = byteCount;
	memcpy(buf, _buf + _pos, bytes);
	return bytes;

}
// set the position in the stream using seekg from fstream
// if the position is larger then the length then return position
i64 CS422::FileStream::SetPosition(i64 position){
	if (_size - 1 < position || position < 0)
		return _pos;
	_pos = position;
	return _pos;
}
// write to the stream and return the lenght of what was just wrote
int CS422::FileStream::Write(const void* buf, int byteCount){
	if (CanWrite()) {
		i64 oldpos = _pos;
		u8 *newbuf = (u8 *)realloc(_buf, _size + byteCount);
		if (newbuf == NULL)
			return -1;
		_buf = newbuf;
		memcpy(_buf + _pos, buf, byteCount);

		if ((_pos + byteCount) > _size)
			_size = _pos + byteCount;
		_pos += byteCount;
		return byteCount;
	}
	return 0;
}
