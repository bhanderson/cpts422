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

#define SUCCESS 0
#define FAILURE -1

using namespace CS422;
using namespace std;

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
char* AllAtOnceWrite(Stream* testStream, u8 data[], int bytes)
{
	if (!testStream->CanWrite())
		return "AllAtOnceWrite Passed";
	testStream->Write(data, bytes);
	int result = WriteVerification(testStream, data, bytes);
	if (result != 0)
	{
		return "AllAtOnceWrite Failed";
	}
	return "AllAtOnceWrite Passed";
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
}

void testFileStream()
{
	ofstream os;// ("c:\\Users\\Bryce\\test.txt", ios::out | ios::in);
	void *beef = "DEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEAD"
				 "BEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFD"
				 "EADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBE"
				 "EFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEFDEADBEEF";

	os.open("c:\\Users\\Bryce\\read.txt");
	os.write((char *)beef, 240);
	os.close();
	FileStream yolo("c:\\Users\\Bryce\\read.txt", ios::in);
	Stream *a = &yolo;
	cout << "Read Tests:\n------------------" << endl;
	cout << InOrderRead(a, (u8 *)beef, (u8 *)beef, (u8 *)beef, 80, 0) << endl;
	cout << ReverseRead(a, (u8 *) beef, (u8 *) beef, (u8 *) beef, 80, 0) << endl;
	cout << RandomRead(a, (u8 *) beef, (u8 *) beef, (u8 *) beef, 80, 0) << endl;
	FileStream write("c:\\Users\\Bryce\\write.txt", ios::out);
	Stream *b = &write;
	cout << "Write Tests:\n----------------" << endl;
	cout << AllAtOnceWrite(b,(u8 *) beef,240) << endl;
	cout << FixedSizeWriteCommon(b) << endl;
	cout << FixedSizeWriteUncommon(b) << endl;
}
int main(int argc, const char* argv[])
{
	//FileStream yolo("C:\\Users\\Bryce\\test.txt", ios::out | ios::in);
	//char c[8];
	//yolo.Read(c, 8);
	//fstream a("c:\\Users\\Bryce\\test.txt", ios::in);
	//a.read(c, 8);
	//printf("%s", c);

	//Stream *Disdain = &yolo;
	testIndexedStream();
	testFileStream();

	//cout << WriteVerification(Disdain, data, 256);
	//cout << InOrderRead(Hate, tests, 2, 0) << endl;
	//cout << InOrderRead(Disdain, tests, 2, 0) << endl;
	//cout << ReverseRead(Hate, tests, 2, 0) << endl;
	//cout << RandomRead(Hate, tests, 2, 0) << endl;
	//cout << AllAtOnceWrite(Hate, data, 256) << endl;
	//cout << FixedSizeWrite(Hate, testValues, writevalues);
	return 0;
}

