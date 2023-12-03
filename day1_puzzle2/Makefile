CC=g++
CFLAGS=-std=c++11 -O0 -g -Wall
LDFLAGS=
SOURCE=main.cpp
#OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(SOURCE:.cpp=.exe)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(EXECUTABLE)

