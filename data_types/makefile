CC=g++
CFLAGS=-Wall -DDEBUG -g

all: list stack queue

clean:
	rm -f *.exe

list: test_list.cpp list.h
	$(CC) $(CFLAGS) test_list.cpp -o list
	
stack: test_stack.cpp stack.h
	$(CC) $(CFLAGS) test_stack.cpp -o stack
	
queue: test_queue.cpp queue.h
	$(CC) $(CFLAGS) test_queue.cpp -o queue