#ifndef SCREEN_H
#define SCREEN_H

#include "game.h"

typedef struct screenRep* Screen;


struct screenRep {

	Node parent;

	SDL_Window* window;
	SDL_Renderer* rend;

	void* screen_data;

	void (*update_screen)(Screen, Input, List);
	void (*render_screen)(Screen); 
	void (*free_screen)(Screen);
};

#include "screen_game.h"
#include "screen_menu.h"

Screen createScreen(void* screen_data, SDL_Window* window, SDL_Renderer* rend,
					void (*update_screen)(Screen, Input, List),
					void (*render_screen)(Screen),
					void (*free_screen)(Screen));

void screenParent(void* o, Node n);
void freeScreen(void*);

#endif
