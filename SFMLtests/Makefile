CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-window -lsfml-system -lsfml-graphics
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=jumpy_mushroom

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
