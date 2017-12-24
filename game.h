#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "objects.h"

#include "player.h"
#include "ball.h"
#include "bullet.h"

#define TITLE "Pong game"
#define POS_UNDF (SDL_WINDOWPOS_UNDEFINED)
#define WIN_WIDTH (480)
#define WIN_HEIGHT (720)

#define N_TYPES 3
#define PLAYERS 0
#define BALL 1
#define BULLETS 2

void checkError(void* ptr, SDL_Window* window, SDL_Renderer* rend);

int startGame(SDL_Window* window, SDL_Renderer* rend);
SDL_Texture* createBackground(SDL_Renderer* rend);

#define min(a, b) (((a) <= (b)) ? (a): (b))
#define max(a, b) (((a) >= (b)) ? (a): (b))

#endif
