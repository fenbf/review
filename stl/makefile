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

all: strings iterators boostTest searching pointers lambda beautiful

.PHONY : clean
clean:
	rm -f *.exe

strings: strings.cpp
	$(CC) $(CFLAGS) $< -o $@
	
iterators: iterators.cpp
	$(CC) $(CFLAGS) $< -o $@
	
boostTest: boostTest.cpp
	$(CC) $(CFLAGS_BOOST) $< -o $@

searching: CFLAGS += -std=c++0x	
searching: searching.cpp
	$(CC) $(CFLAGS) $< -o $@
	
pointers: CFLAGS += -std=c++0x	
pointers: pointers.cpp
	$(CC) $(CFLAGS) $< -o $@
	
lambda: CFLAGS += -std=c++0x	
lambda: lambda.cpp
	$(CC) $(CFLAGS) $< -o $@
	
beautiful: CFLAGS += -std=c++1y	
beautiful: beautiful_std_alg.cpp
	$(CC) $(CFLAGS) $< -o $@