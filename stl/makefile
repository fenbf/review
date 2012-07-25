CC=g++
INCLUDES=../utils/
CFLAGS=-Wall -W -I $(INCLUDES)
CFLAGS_BOOST=$(CFLAGS) -I"$(BOOST_DIR)"

ifeq "$(debug)" "1"
	CFLAGS += -DDEBUG -g
endif

ifeq "$(cpp11)" "1"
	CFLAGS += -std=c++0x
endif

all: strings iterators boostTest

clean:
	rm -f *.exe

strings: strings.cpp
	$(CC) $(CFLAGS) $< -o $@
	
iterators: iterators.cpp
	$(CC) $(CFLAGS) $< -o $@
	
boostTest: boostTest.cpp
	$(CC) $(CFLAGS_BOOST) $< -o $@