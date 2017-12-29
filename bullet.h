#ifndef BULL_H
#define BULL_H

#include "game.h"

#define NONE 0
#define UP 1
#define DOWN 2

#define CHANGE_TIME 25
#define ANIMATION_LENGTH 6

typedef struct bullet* Bullet;

struct bullet {
	int direction;
	int current_sprite;
	int change_sprite;

	SDL_Texture* sprite;
};

Object createBullet(int x, int y, SDL_Texture* tex, SDL_Renderer* rend);
int bullet_EH(Object b, Input in, List screens);
void bullet_render(Object, SDL_Renderer*);
int bullet_col_check(Object b, SDL_Rect* r);

void bullet_update(Object b, List*);

void free_bullet(void * b);

#endif
