CC=gcc
CFLAGS=-lSDL2 -lSDL2_image

pong: pong.o player.o objects.o

pong.o: game.c game.h

player.o: player.c player.h

objects.o: objects.c objects.h


