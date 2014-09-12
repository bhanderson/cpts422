#ifndef CS422_INDEXEDNUMBERSTEAMH
#define CS422_INDEXEDNUMBERSTEAMH
#include "Stream.hpp"
using namespace CS422;

class IndexedNumberStream : public Stream
{
public:
	IndexedNumberStream(int btyeSize);

	// Returns a boolean indicating whether or not this stream can be read from.
	bool CanRead();

	// Returns a boolean indicating whether or not seeking is allowed with this 
	// stream. If this returns true then both the GetPosition and SetPosition 
	// functions will be available for getting and setting the position within 
	// the stream. If it returns false then neither of those functions should be 
	// used.
	bool CanSeek();

	// Returns a boolean indicating whether or not this stream can be written to.
	bool CanWrite();

	// If the stream buffers content before writing it to the final output 
	// destination then calling this method forces any pending data to be fully 
	// written.
	void Flush() { }

	// Returns a 64-bit signed integer indicating the total size of the stream,
	// in bytes. Any negative values returned indicate an error.
	i64 GetLength() const;

	// Returns the current stream position. All valid positions within a stream are 
	// non-negative numbers. A negative return value from this function indicates 
	// an error and that the stream is in an invalid state.
	i64 GetPosition() const;

	// Attempts to read "byteCount" bytes from the stream starting at the current position.
	// Returns the number of bytes successfully read on success. After a successful read 
	// the position of the stream will also be increased by the number of bytes read.
	//
	// Returns 0 if the position was at the end of the stream at the start of the read and 
	// no bytes were read. A return value of 0 must always imply end of stream and not an 
	// actual error.
	//
	// Returns a negative value if an error occurs. The negative-valued error codes will be 
	// specific to the stream type.
	int Read(void* buf, int byteCount);

	// Sets the position of the stream. If the requested stream position is invalid, then 
	// no changes will be made to the stream and the current position will be returned. 
	// If the requested stream position is valid, then it is set as the current stream 
	// position and the new stream position (which will have the same value as the 
	// position parameter) will be returned.
	// If CanSeek() returns false for this stream, implying that the stream doesn't 
	// support seeking, then this method does not alter the state of the stream and 
	// returns -1.
	i64 SetPosition(i64 position);

	// Attempts to write "ByteCount" bytes to the stream starting at the current position.
	// Returns the number of bytes successfully written.
	// Advances the position of the stream by the number of bytes written.
	int Write(const void* buf, int byteCount);
private:
	int ProceduralGenerate();
	bool _canRead;
	bool _canSeek;
	bool _canWrite;
	i64 _position;
	i64 _size;

};

#endif


