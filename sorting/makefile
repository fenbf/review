CC=g++
INCLUDES=../utils/
CFLAGS=-Wall -W -DDEBUG -g -I $(INCLUDES)

all: simple_sort

clean:
	rm -f *.exe

simple_sort: simple_sort.cpp
	$(CC) $(CFLAGS) simple_sort.cpp -o simple_sort
	
