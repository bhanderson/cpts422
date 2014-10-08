// HW 6 - Echo server exploit
// THIS is the file that you need to modify this file for this assignment

#include <iostream>
#include <string>
#include "TCPComm.h"

using namespace std;
using namespace CS422;

void GotData(TCPComm* comm, unsigned char* data, int dataLength)
{
	char* buf = new char[dataLength + 1];
	memcpy(buf, data, dataLength);
	buf[dataLength] = 0;

	cout << endl;
	cout << "Got from server: " << buf << endl;
	cout << "Enter a string to send to the server: ";
}

int main(int argc, const char* argv[])
{
	TCPComm* comm = NULL;
	if (true)
	{
		// Better practice would be to check the command line arguments 
		// for a host name. But this assignment isn't exactly about 
		// illustrating best practices...
		comm = TCPComm::Create("localhost", 42200);
	}

	if (!comm)
	{
		cout << "Could not connect to server" << endl;
		cout << "Make sure the server is running first then re-run this client" << endl;
		return -1;
	}

	// Set up callback for when server sends us data
	comm->OnDataReceived = GotData;

	// Send the handshake
	char* handshake = "422 echo server handshake";
	comm->Send(handshake, strlen(handshake) + 1);

	while (true)
	{
		cout << "Enter a string to send to the server: ";
		string line;
		getline(cin, line);

		if (line.empty()) { break; }

		// Send the string, including the null-terminator
		char* buf = new char[3 + line.size()];
		strcpy(&buf[2], line.c_str());
		((unsigned short*)buf)[0] = (unsigned short)(3 + line.size());
		comm->Send(buf, line.size() + 3);
		delete[] buf;
	}

	cout << "Done" << endl;
}