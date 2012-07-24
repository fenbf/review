CC=g++
INCLUDES=../utils/
CFLAGS=-Wall -W -DDEBUG -g -I $(INCLUDES)

all: strings iterators

clean:
	rm -f *.exe

strings: strings.cpp
	$(CC) $(CFLAGS) strings.cpp -o strings
	
iterators: iterators.cpp
	$(CC) $(CFLAGS) iterators.cpp -o iterators
