CC=gcc
CFLAGS=-g -lSDL2 -lSDL2_image -lm 
OBJS=List.o player.o objects.o ball.o bullet.o screens.o screen_game.o 

game: $(OBJS) game.c game.h
	$(CC) -o pong $(OBJS) game.c $(CFLAGS)

List.o: List.c List.h

player.o: player.c player.h

objects.o: objects.c objects.h

screens.o: screens.c screens.h

screen_game.o: screen_game.c screen_game.h 

ball.o: ball.c ball.h

bullet.o: bullet.c bullet.h

clean:
	rm pong *.o
