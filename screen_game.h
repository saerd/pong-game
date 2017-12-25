#ifndef S_GAME_H
#define S_GAME_H

#include "screens.h"

#define N_TYPES 3
#define PLAYERS 0
#define BALL 1
#define BULLETS 2

Screen createGameScreen(SDL_Window* window, SDL_Renderer* rend);
void updateGameScreen(Screen s, SDL_Event* e, const unsigned char* key_states);
void renderGameScreen(Screen s);
void freeGameScreen(Screen s);

#endif
