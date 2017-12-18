#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "objects.h"
#include "player.h"
#include "ball.h"

#define TITLE "Pong game"
#define POS_UNDF (SDL_WINDOWPOS_UNDEFINED)
#define WIN_WIDTH (640)
#define WIN_HEIGHT (480)

#define LEFT (SDL_SCANCODE_LEFT)
#define RIGHT (SDL_SCANCODE_RIGHT)


void checkError(void* ptr, SDL_Window* window, SDL_Renderer* rend);

void startGame(SDL_Window* window, SDL_Renderer* rend);


#define min(a, b) (((a) <= (b)) ? (a): (b))
#define max(a, b) (((a) >= (b)) ? (a): (b))

#endif
