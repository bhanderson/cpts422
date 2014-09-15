// Cpt S 422 HW2

#include <iostream>
#include <vector>
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
	testStream->Read(read, bytes);
	if (memcmp(read, values, bytes) == 0)
		return SUCCESS;
	return FAILURE;

}
char* FixedSizeWriteCommon(Stream* testStream)
{
	if (!testStream->CanWrite)
		return "Test Passed";
	u8 common[1024] = { 'a' };
	for (int i = 0; i < 4; i++)
	{
		testStream->Write(common, 256);
	}
	int result = WriteVerification(testStream, common, 1024);
	if (result != SUCCESS)
		return "Test Failed";
	return "Test Passed";
}
char *FixedSizeWriteUncommon(Stream* testStream){
	if (!testStream->CanWrite)
		return "Test Passed";
	u8 uncommon[1801] = { 'b' };
	for (int i = 0; i < 5; i++){
		testStream->Write(uncommon, 360);
	}
	testStream->Write(uncommon, 1);
	int result = WriteVerification(testStream, uncommon, 1801);
	if (result != SUCCESS)
		return "Test Failed";
	return "Test Passed";

}
char* AllAtOnceWrite(Stream* testStream, u8 data[], int bytes)
{
	if (!testStream->CanWrite)
		return "Test Passed";
	testStream->Write(data, bytes);
	int result = WriteVerification(testStream, data, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}
int ReadVerification(Stream* testStream, u8* values, int bytes)
{
	if (!testStream->CanRead())
	{
		return 0;
	}
	u8* result = new u8[bytes];
	int bytesRead;
	bytesRead = testStream->Read(result, bytes);
	if (bytes != bytesRead)
	{
		return -1;
	}
	if (memcmp(values, result, bytes) != 0)
	{
		return -1;
	}
	return 0;
}
char* InOrderRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	result = ReadVerification(testStream, values2, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	result = ReadVerification(testStream, values3, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}

char* ReverseRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition+ 2*bytes);
	result = ReadVerification(testStream, values3, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values2, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}
char* RandomRead(Stream* testStream, u8 values1[], u8 values2[], u8 values3[], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values2, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition + 2*bytes);
	result = ReadVerification(testStream, values3, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values1, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
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

}
int main(int argc, const char* argv[])
{
	FileStream yolo("C:\\%username$\test.txt", ios::out | ios::in);
	Stream *Disdain = &yolo;
	testIndexedStream();
	//cout << WriteVerification(Disdain, data, 256);
	//cout << InOrderRead(Hate, tests, 2, 0) << endl;
	//cout << InOrderRead(Disdain, tests, 2, 0) << endl;
	//cout << ReverseRead(Hate, tests, 2, 0) << endl;
	//cout << RandomRead(Hate, tests, 2, 0) << endl;
	//cout << AllAtOnceWrite(Hate, data, 256) << endl;
	//cout << FixedSizeWrite(Hate, testValues, writevalues);
	return 0;
}

