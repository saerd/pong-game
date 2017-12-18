#ifndef PLAY_H
#define PLAY_H

#include "game.h"

#define P1_LEFT (SDL_SCANCODE_LEFT)
#define P1_RIGHT (SDL_SCANCODE_RIGHT)

#define P2_LEFT (SDL_SCANCODE_A)
#define P2_RIGHT (SDL_SCANCODE_S)



typedef struct player* Player;

struct player {
	int left_button;
	int right_button;
	int moving;
	int direction;
};

Object createPlayer(int pNum, SDL_Renderer* rend);
void player_EH(Object p, SDL_Event *e, const unsigned char * key_states);
void player_update(Object p, List);
void free_player(void*);

#endif
