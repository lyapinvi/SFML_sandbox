CC=g++
CFLAGS=-c -Wall -std=c++17
LDFLAGS=-lsfml-window -lsfml-system -lsfml-graphics
SOURCES=main.cpp Snake.cpp World.cpp Game.cpp Window.cpp Textbox.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=snake

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
