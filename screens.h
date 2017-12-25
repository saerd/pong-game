#ifndef SCREEN_H
#define SCREEN_H

#include "game.h"

typedef struct screenRep* Screen;

#include "screen_game.h"

struct screenRep {
	SDL_Window* window;
	SDL_Renderer* rend;

	void* objects;

	void (*update_screen)(Screen, SDL_Event*, const unsigned char*);
	void (*render_screen)(Screen); 
	void (*free_screen)(Screen);
};

Screen createScreen(void* objects, SDL_Window* window, SDL_Renderer* rend,
					void (*update_screen)(Screen, SDL_Event*, const unsigned char*),
					void (*render_screen)(Screen),
					void (*free_screen)(Screen));

#endif
