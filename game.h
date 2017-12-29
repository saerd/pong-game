#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct input* Input;

// implementation of input that has the Event struct, key states array and 3 variables describing
// the state of the mouse

struct input {
	SDL_Event* event;
	const unsigned char* key_states;
	int mouse_x;
	int mouse_y;
	unsigned int mask;
};

Input createInput(void);
int updateInput(Input);
void freeInput(Input in);
int filterMouseMotion(void* d, SDL_Event* event);

#include "List.h"


#include "objects.h"

#include "button.h"
#include "player.h"
#include "ball.h"
#include "bullet.h"

#include "screens.h"


#define TITLE "Pong game"
#define POS_UNDF (SDL_WINDOWPOS_UNDEFINED)
#define WIN_WIDTH (600)
#define WIN_HEIGHT (900)


void checkError(void* ptr, SDL_Window* window, SDL_Renderer* rend);
void begin_app(SDL_Window* window, SDL_Renderer* rend);


SDL_Texture* createBackground(SDL_Renderer* rend);

#define min(a, b) (((a) <= (b)) ? (a): (b))
#define max(a, b) (((a) >= (b)) ? (a): (b))

#endif
