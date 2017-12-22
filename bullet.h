#ifndef BULL_H
#define BULL_H

#include "game.h"

#define UP 0
#define DOWN 1

typedef struct ball* Ball;

struct bullet {
	int direction;
	int current_sprite;
};

Object createBullet(SDL_Renderer* rend);
void bullet_EH(Object b, SDL_Event *e, const unsigned char * key_states);
void bullet_render(Object, SDL_Renderer*);
int bullet_col_check(Object b, SDL_Rect* r);

void bullet_update(Object b, List*);

void free_bullet(void * b);

#endif
