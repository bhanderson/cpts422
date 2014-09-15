// Cpt S 422 HW2

#include <iostream>
#include <vector>
#include "Stream.hpp"
#include "IndexedNumberStream.hpp"
#include "FileStream.hpp"

using namespace CS422;
using namespace std;

int VerifyWrite(Stream *testStream, char *values, int bytes){
	char *temp = (char *) malloc(bytes);

	if (testStream->GetPosition() != bytes)
		goto error;

	testStream->SetPosition(0);
	testStream->Read(temp, bytes);
	if (strcmp(values, temp) == 0){
		goto out;
	}
	goto error;
out:
	free(temp);
	return 0;
error:
	free(temp);
	return -1;
}

int WriteVerification(Stream* testStream, char* values, int bytes)
{
	if (!testStream->CanWrite())
	{
		return 0;
	}
	int written = testStream->Write(values, bytes);
	if (written == bytes){
		if (VerifyWrite(testStream, values, bytes) == 0){
			return 0;
		}
	}
	return -1;
}
char* FixedSizeWrite(Stream* testStream, char data[][3], int bytes[])
{
	int result;
	for (int i = 0; i < 3; i++)
	{
		result = WriteVerification(testStream, data[i], bytes[i]);
		if (result != 0)
		{
			return "Test Failed";
		}
	}
	return "Test Passed";
}
char* AllAtOnceWrite(Stream* testStream, char data[], int bytes)
{
	int result;
	result = WriteVerification(testStream, data, bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}
int ReadVerification(Stream* testStream, char* values, int bytes)
{
	if (!testStream->CanRead())
	{
		return 0;
	}
	char* result = new char[bytes];
	int bytesRead;
	bytesRead = testStream->Read(result, bytes);
	if (bytes != bytesRead)
	{
		return -1;
	}
	if (strcmp(values, result) != 0)
	{
		return -1;
	}
	return 0;
}
char* InOrderRead(Stream* testStream, char values[][3], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values[0], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	result = ReadVerification(testStream, values[1], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	result = ReadVerification(testStream, values[2], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}
char* ReverseRead(Stream* testStream, char values[][3], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition+ 2*bytes);
	result = ReadVerification(testStream, values[2], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values[1], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values[0], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}
char* RandomRead(Stream* testStream, char values[][3], int bytes, int startPosition)
{
	int result;
	testStream->SetPosition(startPosition + bytes);
	result = ReadVerification(testStream, values[1], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition + 2*bytes);
	result = ReadVerification(testStream, values[2], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	testStream->SetPosition(startPosition);
	result = ReadVerification(testStream, values[0], bytes);
	if (result != 0)
	{
		return "Test Failed";
	}
	return "Test Passed";
}

int main(int argc, const char* argv[])
{
	FileStream yolo("C:\\%username$\test.txt", ios::out | ios::in);
	IndexedNumberStream fuckIt(10);
	Stream *Hate = &fuckIt;
	Stream *Disdain = &yolo;
	cout << WriteVerification(Disdain, data, 256);
	//cout << InOrderRead(Hate, tests, 2, 0) << endl;
	//cout << InOrderRead(Disdain, tests, 2, 0) << endl;
	//cout << ReverseRead(Hate, tests, 2, 0) << endl;
	//cout << RandomRead(Hate, tests, 2, 0) << endl;
	//cout << AllAtOnceWrite(Hate, data, 256) << endl;
	//cout << FixedSizeWrite(Hate, testValues, writevalues);
	return 0;
}

