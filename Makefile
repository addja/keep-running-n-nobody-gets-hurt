BIN=game
CC=g++
CFLAGS=-Wall
SFMLFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=-lGL -lGLEW

OBJ =main.o cGame.o cGraphics.o cTexture.o cData.o cModel.o

all: main

main: $(OBJ)
		$(CC) $(OBJ) -o $(BIN) $(SFMLFLAGS) $(LDFLAGS)
			
main.o: src/main.cpp
		$(CC) $(CFLAGS) -c src/main.cpp

cGame.o: src/cGame.cpp
		$(CC) $(CFLAGS) -c src/cGame.cpp

cGraphics.o: src/cGraphics.cpp
		$(CC) $(CFLAGS) -c src/cGraphics.cpp

cTexture.o: src/cTexture.cpp
		$(CC) $(CFLAGS) -c src/cTexture.cpp
		
cData.o: src/cData.cpp
		$(CC) $(CFLAGS) -c src/cData.cpp

cModel.o: src/cModel.cpp
		$(CC) $(CFLAGS) -c src/cModel.cpp	

.PHONY: clean

run: clean all
		./$(BIN)

clean:
		rm -f $(OBJ) $(BIN)
