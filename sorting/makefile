CC=g++
INCLUDES=../utils/
CFLAGS=-Wall -W -I $(INCLUDES)

all: simple_sort

debug: CFLAGS += -DDEBUG -g
debug: all

clean:
	rm -f *.exe

simple_sort: simple_sort.cpp
	$(CC) $(CFLAGS) simple_sort.cpp -o simple_sort
	
