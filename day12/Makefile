CC=g++
CFLAGS=-std=c++11 -O0 -g -Wall -Wno-sign-compare
LDFLAGS=

SOURCES=puzzle1.cpp puzzle2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLES=$(SOURCES:.cpp=.exe)

all: $(EXECUTABLES)

# Rule to compile the source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Rule to link the program
%.exe: %.o
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES) $(OBJECTS)

# Declare non-file targets as PHONY
.PHONY: all clean