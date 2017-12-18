#ifndef BALL_H
#define BALL_H

#include "game.h"

typedef struct ball* Ball;

struct ball {
	int rise;
	int run;
};

Object createBall(SDL_Renderer* rend);
void ball_EH(Object b, SDL_Event *e, const unsigned char * key_states);
void ball_update(Object b);

#endif
