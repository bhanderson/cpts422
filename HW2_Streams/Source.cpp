// Cpt S 422 HW2

#include <iostream>
#include "Stream.hpp"
#include "IndexedNumberStream.hpp"

using namespace CS422;
using namespace std;

int WriteVerification(Stream* testStream, char* values, int bytes)
{
	if (!testStream->CanWrite())
	{
		return 0;
	}

	testStream->Write(values, bytes);
	return 0;
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
	// In other files you will implement the classes that inherit from stream.
	// Create instances of such objects as needed here (make sure you are creating 
	// each type of stream that you implemented).
	// Write Stream unit testing functions and kick off the tests from here in main.
	IndexedNumberStream fuckIt(512);
	Stream* Hate = &fuckIt;
	unsigned char* temp = new unsigned char[512];
	fuckIt.Read(temp, 512);
	for (int i = 0; i < 512; i++)
	{
		printf("%d\n", temp[i]);
	}
	cout << temp << endl;
	char resultValues[] = "BB";
	char tests[3][3] = { "BB", "BB", "BB" };
	char data[256] = "Hello my name is INSERT USER NAME HERE and I am feeling INSERT USER FEELING HERE, my favorite color is INSERT USER SELECTED COLOR HERE, and I leave on INSERT ADDRESS OF USER HERE, and most important I am 256 characters long with just a bit oh help I can m";
	char testValues[3][10] = { "My Name", "is what", "is who" };
	int writevalues[3] = { 10, 10, 10 };
	cout << InOrderRead(Hate, tests, 2, 0) << endl;
	cout << ReverseRead(Hate, tests, 2, 0) << endl;
	cout << RandomRead(Hate, tests, 2, 0) << endl;
	cout << AllAtOnceWrite(Hate, data, 256) << endl;
	//cout << FixedSizeWrite(Hate, testValues, writevalues);



	return 0;
}

