CC=gcc
CFLAGS=-lSDL2 -lSDL2_image

pong: game.c
	$(CC) -o pong game.c $(CFLAGS)

