#include "game.h"

typedef int (*Screen)();

typedef Screen (*fncptr)(SDL_Window*, SDL_Renderer*);

Screen startGame(SDL_Window* window, SDL_Renderer* rend);
Screen menuScreen(SDL_Window* window, SDL_Renderer* rend);
