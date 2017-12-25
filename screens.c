#include "screens.h"

Screen createScreen(void* objects, SDL_Window* window, SDL_Renderer* rend,
					void (*update_screen)(Screen, SDL_Event*, const unsigned char*),
					void (*render_screen)(Screen),
					void (*free_screen)(Screen)){

	Screen s = malloc(sizeof(struct screenRep));
	s->window = window;
	s->rend = rend;

	s->objects = objects;

	s->render_screen = render_screen;
	s->update_screen = update_screen;
	s->free_screen = free_screen;

	return s;
}
