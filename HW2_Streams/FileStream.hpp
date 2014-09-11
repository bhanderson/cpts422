#ifndef __FILESTREAM_HPP__
#define __FILESTREAM_HPP__

#include "Stream.hpp"
#include <fstream>
#include <string>

namespace CS422
{
	class FileStream : Stream
	{
	public:
		FileStream(std::string path, std::ios_base::openmode mode);
		~FileStream();
		bool CanRead();
		bool CanSeek();
		bool CanWrite();
		void Flush();
		i64 GetLength();
		i64 GetPosition();
		int Read(void* buf, int byteCount);
		i64 SetPosition(i64 position);
		int Write(const void* buf, int byteCount);



	private:
		std::fstream _buf;
		bool _readable = false;
		bool _writable = false;
		bool _seekable = false;
	};
}

#endif