CC=gcc
CFLAGS=-lSDL2 -lSDL2_image -lm
OBJS=player.o objects.o ball.o bullet.o screens.o

game: $(OBJS) game.c game.h
	$(CC) -o pong $(OBJS) game.c $(CFLAGS)

player.o: player.c player.h

screens.o: screens.c screens.h

objects.o: objects.c objects.h

ball.o: ball.c ball.h

bullet.o: bullet.c bullet.h

clean:
	rm pong *.o
