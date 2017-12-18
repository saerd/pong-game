CC=gcc
CFLAGS=-lSDL2 -lSDL2_image
OBJS=player.o objects.o ball.o

game: $(OBJS) game.c
	$(CC) -o pong $(OBJS) game.c $(CFLAGS)

player.o: player.c player.h

objects.o: objects.c objects.h

ball.o: ball.c ball.h

clean:
	rm pong *.o
