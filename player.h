#ifndef PLAY_H
#define PLAY_H

#include "game.h"

#define P1_LEFT (SDL_SCANCODE_LEFT)
#define P1_RIGHT (SDL_SCANCODE_RIGHT)
#define P1_SHOOT (SDL_SCANCODE_UP)

#define P2_LEFT (SDL_SCANCODE_A)
#define P2_RIGHT (SDL_SCANCODE_D)
#define P2_SHOOT (SDL_SCANCODE_W)

#define RESTOCK_TIME 300
#define RELOAD_TIME 40
#define MAX_BULLETS 3

typedef struct player* Player;

struct player {
	int left_button;
	int right_button;
	int shoot_button;

	int moving;
	int direction;

	int shoot;
	int reload;
	int restock;

	int n_bullets;

	SDL_Texture* bullet_tex;
};

Object createPlayer(int pNum, SDL_Renderer* rend);
int player_EH(Object p, Input in, List screens);
void player_update(Object p, List*);
void player_render(Object, SDL_Renderer*);
int player_col_check(Object p, SDL_Rect* r);
void free_player(void*);

#endif
