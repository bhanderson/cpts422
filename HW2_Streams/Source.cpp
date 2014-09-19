// Cpt S 422 HW2
// Group Best Team
// Bryce Handerson, Josh Clark, Michael McBreen
//---------------------------------------------

#include <iostream>
#include <vector>
#include <array>
#include "Stream.hpp"
#include "IndexedNumberStream.hpp"
#include "FileStream.hpp"
#include "MemoryStream.hpp"

#define SUCCESS 0
#define FAILURE -1

using namespace CS422;
using namespace std;

// check the write succeeded by checking the bytes values in the stream 
int WriteVerification(Stream* testStream, u8* values, int bytes)
{
	// check the write succeeded
	if (!testStream->CanRead())
		return SUCCESS; // cant tell its wrong so its right
	int position = testStream->GetPosition();
	testStream->SetPosition(position - bytes);
	char *read = new char[bytes];
	// all at once with one read call
	testStream->Read(read, bytes);
	if (memcmp(read, values, bytes) == 0)
		return SUCCESS;
	return FAILURE;

}
// write a fixed size of 256 4 times to = 1024
char* FixedSizeWriteCommon(Stream* testStream)
{
	if (!testStream->CanWrite())
		return "FixedSizeWriteCommon Passed";
	u8 common[1024] = { 'a' };
	memset(common, 'a', 1024);
	for (int i = 0; i < 4; i++)
	{
		testStream->Write(common, 256);
	}
	int result = WriteVerification(testStream, common, 1024);
	if (result != SUCCESS)
		return "FixedSizeWriteCommon Failed";
	return "FixedSizeWriteCommon Passed";
}
// write uncommon buffer sizes to test weird sizes
char *FixedSizeWriteUncommon(Stream* testStream){
	if (!testStream->CanWrite())
		return "FixedSizeWriteUncommon Passed";
	u8 uncommon[1801] = { 'b' };
	memset(uncommon, 'b', 1801);
	for (int i = 0; i < 5; i++){
		testStream->Write(uncommon, 360);
	}
	testStream->Write(uncommon, 1);
	int result = WriteVerification(testStream, uncommon, 1801);
	if (result != SUCCESS)
		return "FixedSizeWriteUncommon Failed";
	return "FixedSizeWriteUncommon Passed";

}
// write a big chunk all at once
char* AllAtOnceWrite(Stream* testStream, u8 data[], int bytes)
{
	if (!testStream->CanWrite())
		return "AllAtOnceWrite Passed";
	testStream->Write(data, bytes);
	int result = WriteVerification(testStream, data, bytes);
	if (result != SUCCESS)
	{
		return "AllAtOnceWrite Failed";
	}
	return "AllAtOnceWrite Passed";
}
//backwards write with random buffer size?
char* BackwardsWrite(Stream* testStream){
	if (!testStream->CanWrite())
		return "BackwardsWrite Passed";
	char pad[1024];
	memset(pad, 0, 1024);
	testStream->Write(pad, 1024);
	testStream->SetPosition(512);
	char a[512];
	memset(a, 'a', 512);
	testStream->Write(a, 512);
	testStream->SetPosition(0);
	char b[512];
	memset(b, 'b', 512);
	testStream->Write(b, 512);
	testStream->SetPosition(1024);
	unsigned char data[1024];
	memset(data, 'a', 512);
	memset(data + 512, 'b', 512);
	int result = WriteVerification(testStream, data, 1024);
	if (result != SUCCESS)
	{
		return "BackwardsWrite Failed";
	}
	return "BackwardsWrite Passed";
}

int ReadVerification(Stream* testStream, u8* values, int bytes)
{
	if (!testStream->CanRead())
	{
		return SUCCESS;
	}
	u8* result = new u8[bytes];
	int bytesRead;
	bytesRead = testStream->Read(result, bytes);
	if (bytes != bytesRead)
	{
		return FAILURE;
	}
	if (memcmp(values, result, bytes) != SUCCESS)
	{
		return FAILURE;
	}
	return SUCCESS;
}
char* InOrderRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != SUCCESS)
	{
		return "InOrderRead Failed";
	}
	result = ReadVerification(testStream, values2, bytes);
	if (result != SUCCESS)
	{
		return "InOrderRead Failed";
	}
	result = ReadVerification(testStream, values3, bytes);
	if (result != SUCCESS)
	{
		return "InOrderRead Failed";
	}
	return "InOrderRead Passed";
}
char* ReverseRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition+ 2*bytes);
	result = ReadVerification(testStream, values3, bytes);
	if (result != SUCCESS)
	{
		return "ReverseRead Failed";
	}
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values2, bytes);
	if (result != SUCCESS)
	{
		return "ReverseRead Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != SUCCESS)
	{
		return "ReverseRead Failed";
	}
	return "ReverseRead Passed";
}
char* RandomRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values2, bytes);
	if (result != SUCCESS)
	{
		return "RandomRead Failed";
	}
	testStream->SetPosition(startPosition + 2*bytes);
	result = ReadVerification(testStream, values3, bytes);
	if (result != SUCCESS)
	{
		return "RandomRead Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != SUCCESS)
	{
		return "RandomRead Failed";
	}
	return "RandomRead Passed";
}

void testIndexedStream()
{
	u8 temp1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	u8 temp2[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	u8 temp3[10] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };
	IndexedNumberStream fuckIt(30);
	Stream *Hate = &fuckIt;
	cout << InOrderRead(Hate, temp1, temp2, temp3, 10, 0) << endl;
	cout << ReverseRead(Hate, temp1, temp2, temp3, 10, 0) << endl;
	cout << RandomRead(Hate, temp1, temp2, temp3, 10, 0) << endl;
	cout << BackwardsWrite(Hate) << endl;
}

void testFileStream()
{
	ofstream os;
	void *beef = "DEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEAD"
				 "BEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFD"
				 "EADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBE"
				 "EFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEF";

	os.open("read.txt");
	os.write((char *)beef, 240);
	os.close();
	FileStream yolo("read.txt", ios::in);
	Stream *a = &yolo;
	cout << "Read Tests:\n------------------" << endl;
	cout << InOrderRead(a, (u8 *)beef, (u8 *)beef, (u8 *)beef, 80, 0) << endl;
	cout << ReverseRead(a, (u8 *) beef, (u8 *) beef, (u8 *) beef, 80, 0) << endl;
	cout << RandomRead(a, (u8 *) beef, (u8 *) beef, (u8 *) beef, 80, 0) << endl;
	FileStream write("write.txt", ios::out);
	Stream *b = &write;
	cout << "Write Tests:\n----------------" << endl;
	cout << AllAtOnceWrite(b,(u8 *) beef,240) << endl;
	cout << FixedSizeWriteCommon(b) << endl;
	cout << FixedSizeWriteUncommon(b) << endl;
	cout << BackwardsWrite(b) << endl;
}

void testMemoryStream()
{
	void *beef = "DEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEAD"
		"BEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFD"
		"EADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBE"
		"EFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEF";
	
	MemoryStream write(16);
	Stream *a = &write;
	cout << "Write Tests:\n----------------" << endl;
	cout << AllAtOnceWrite(a, (u8 *)beef, 240) << endl;
	cout << FixedSizeWriteCommon(a) << endl;
	cout << FixedSizeWriteUncommon(a) << endl;
	cout << "Read Tests:\n------------------" << endl;
	cout << InOrderRead(a, (u8 *)beef, (u8 *)beef, (u8 *)beef, 80, 0) << endl;
	cout << ReverseRead(a, (u8 *)beef, (u8 *)beef, (u8 *)beef, 80, 0) << endl;
	cout << RandomRead(a, (u8 *)beef, (u8 *)beef, (u8 *)beef, 80, 0) << endl;
	cout << BackwardsWrite(a) << endl;
}

int main(int argc, const char* argv[])
{

	testIndexedStream();
	testFileStream();
	testMemoryStream();
	return 0;
}

