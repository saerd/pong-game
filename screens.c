#include "screens.h"

Screen createScreen(void* screen_data, SDL_Window* window, SDL_Renderer* rend,
					void (*update_screen)(Screen, Input, List),
					void (*render_screen)(Screen),
					void (*free_screen)(Screen)){

	if(!(window && rend && update_screen && render_screen && free_screen)) return NULL;

	// simple function that mallocs space and fills all fields
	Screen s = malloc(sizeof(struct screenRep));

	s->parent = NULL;

	s->window = window;
	s->rend = rend;

	s->screen_data = screen_data;

	s->render_screen = render_screen;
	s->update_screen = update_screen;
	s->free_screen = free_screen;

	return s;
}

// For use with Lists
void screenParent(void* o, Node n){
	Screen scr = o;
	scr->parent = n;
}

void freeScreen(void* o){
	Screen s = o;
	s->free_screen(s);
}
