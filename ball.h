#ifndef BALL_H
#define BALL_H

#include "game.h"

#define NORMAL 0
#define INCREASE 1
#define DECREASE 2

#define RISE 0
#define RUN 1

typedef struct ball* Ball;

struct ball {
	int rise;
	int run;
	int current_sprite;
	int done;
};

Object createBall(SDL_Renderer* rend);
void ball_EH(Object b, SDL_Event *e, const unsigned char * key_states);
void ball_render(Object, SDL_Renderer*);
int ball_col_check(Object b, SDL_Rect* r);

void ball_update(Object b, List*);
void ballSpeed(Ball b, int flag);
void reverseBall(Ball b, int flag);

void free_ball(void * b);

#endif
