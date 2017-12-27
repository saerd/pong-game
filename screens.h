#ifndef SCREEN_H
#define SCREEN_H

#include "game.h"

// This is an implementation of displaying a 'Screen'
// it requires three functions as follows
// 	1.	update_screen - a function that can update itself given Input (see game.h) and a Stack (List)
// 						of screens (see below how this works)
// 	2.	render_screen - a function that can render all its content that it chooses (stored in screen_data)
// 	3.	free_screen - a way to free all its assets
//
// handling Screens is done using a stack (generic List, see List.h)
// conventionally it should only call update_screen for a screen that is at the tail (top of the stack)
// and then call render screen for everything afterwards
// this gives the screen at the top the ability to pop itself, delete everything, or add another
// screen while everything below stays 'still'


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
