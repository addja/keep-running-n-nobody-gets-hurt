BIN=game
CC=g++
CFLAGS=-Wall
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=-lGL -lGLEW

OBJ =main.o cGame.o cGraphics.o

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(SFMLFLAGS) $(LDFLAGS)
	
main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp

cGame.o: src/cGame.cpp
	$(CC) $(CFLAGS) -c src/cGame.cpp

cGraphics.o: src/cGraphics.cpp
	$(CC) $(CFLAGS) -c src/cGraphics.cpp

.PHONY: clean

run: all
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
