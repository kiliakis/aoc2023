CC=g++
CFLAGS=-std=c++11 -O0 -g -Wall
LDFLAGS=

SOURCE=main.cpp
OBJECTS=$(SOURCE:.cpp=.o)
EXECUTABLE=$(SOURCE:.cpp=.exe)

all: $(EXECUTABLE)

# Rule to compile the source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Rule to link the program
$(EXECUTABLE): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)

# Declare non-file targets as PHONY
.PHONY: all clean