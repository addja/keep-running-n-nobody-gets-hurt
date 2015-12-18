BIN=game
CC=g++
CFLAGS=-Wall -O3
SFMLFLAGS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
LDFLAGS=-lGL -lGLEW

OBJ =cSound.o cMusic.o cMenu.o cGraphics.o cTexture.o cData.o cModel.o cEntity.o cPlayer.o cScene.o main.o cGame.o 

all: main

main: $(OBJ)
		$(CC) $(OBJ) -o $(BIN) $(SFMLFLAGS) $(LDFLAGS)
			
main.o: src/main.cpp
		$(CC) $(CFLAGS) -c src/main.cpp

cMenu.o: src/cMenu.cpp
		$(CC) $(CFLAGS) -c src/cMenu.cpp

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

cEntity.o: src/cEntity.cpp
		$(CC) $(CFLAGS) -c src/cEntity.cpp	

cPlayer.o: src/cPlayer.cpp
		$(CC) $(CFLAGS) -c src/cPlayer.cpp	

cScene.o: src/cScene.cpp
		$(CC) $(CFLAGS) -c src/cScene.cpp	

cSound.o: src/cSound.cpp
		$(CC) $(CFLAGS) -c src/cSound.cpp	

cMusic.o: src/cMusic.cpp
		$(CC) $(CFLAGS) -c src/cMusic.cpp	

.PHONY: clean

run: clean all
		./$(BIN)

clean:
		rm -f $(OBJ) $(BIN)
