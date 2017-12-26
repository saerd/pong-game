#ifndef OBJ_H
#define OBJ_H

#include "game.h"

typedef struct object* Object;

struct object {

	Node parent;

	SDL_Rect colBox;
	SDL_Texture* tex;
	SDL_Renderer* rend;
	void* data;

	int (*event_handle) (Object, Input, List);
	void (*update_object) (Object, List*);
	void (*render_object) (Object, SDL_Renderer*);
	int (*collision_check) (Object, SDL_Rect*);

	void (*freeData) (void*);
};

Object createObject(SDL_Texture* tex, SDL_Renderer* rend,
					int (*event_handle)(Object, Input, List), 
					void (*update_object)(Object, List*), 
					void (*render_object)(Object, SDL_Renderer*),
					int  (*collision_check)(Object, SDL_Rect*),
					void (*freeData)(void*));

void freeObject(void*);
void object_parent(void* o, Node p);

int check_rect(SDL_Rect*, SDL_Rect*);

#endif


