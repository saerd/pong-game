#ifndef OBJ_H
#define OBJ_H

#include "game.h"

typedef struct object* Object;

struct object {
	SDL_Rect colBox;
	SDL_Texture* tex;
	void* data;

	void (*event_handle) (Object, SDL_Event*, const unsigned char*);
	void (*update_object) (Object);
};

Object createObject(SDL_Texture* tex, void (*event_handle)(Object, SDL_Event*, const unsigned char*), void (*update_object)(Object));

void renderObject(Object obj, SDL_Renderer *rend);

#endif


