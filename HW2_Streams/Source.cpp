// Cpt S 422 HW2

#include <iostream>
#include "Stream.hpp"
#include "FileStream.hpp"

using namespace CS422;

int main(int argc, const char* argv[])
{
	// In other files you will implement the classes that inherit from stream.
	// Create instances of such objects as needed here (make sure you are creating 
	// each type of stream that you implemented).
	// Write Stream unit testing functions and kick off the tests from here in main.
	std::string s = "C:\\Users\\Bryce\\.bash_history";
	FileStream fs(s, std::ios_base::binary);
	return 0;
}