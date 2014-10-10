CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-pthread
SOURCES=Client.cpp TCPComm.cpp
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=Client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

