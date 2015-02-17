CC=g++
INCLUDES=../utils/
CFLAGS=-Wall -W -I $(INCLUDES)
CFLAGS_BOOST=$(CFLAGS) -I"$(BOOST_DIR)"

ifeq "$(debug)" "1"
	CFLAGS += -DDEBUG -g
endif

ifeq "$(cpp11)" "1"
	CFLAGS += -std=c++1y
endif

all: nonstatic_members_init

.PHONY : clean
clean:
	rm -f *.exe
	
nonstatic_members_init: CFLAGS += -std=c++1y	
nonstatic_members_init: nonstatic_members_init.cpp
	$(CC) $(CFLAGS) $< -o $@