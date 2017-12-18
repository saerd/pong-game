#ifndef PLAY_H
#define PLAY_H

#include "game.h"

typedef struct player* Player;

struct player {
	int moving;
	int direction;
};

Object createPlayer(int pNum, SDL_Renderer* rend);
void player_EH(Object p, SDL_Event *e, const unsigned char * key_states);
void player_update(Object p);

#endif
