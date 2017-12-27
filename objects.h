#ifndef OBJ_H
#define OBJ_H

#include "game.h"

// This is my implementation for any object that one would like to update and render in the window
// it needs to be given 4 functions as follows:
// 	1.	event_handle - that can modify itself and a Screen (see screens.h) Stack (implemented as a List) , given Input, this is possible because the screen it belongs to is always at the tail
// 			it should return 0 if it deletes the screen it belongs to from the stack
// 	2.	update_object - that can modify itself given an array of List of all objects it can interact with.
// 			it can choose to delete itself using parent (only !NULL if its been added to a list)
// 			because of the way objects are iterated through, it is safe to delete itself.
// 			not conventional to modify other objects here, however there isnt any other way to
// 	3.	render_object - whether its texture is a full animation sprite or just a simple colour, a
// 			way to render itself must be provided, technically you can separate the logic for the
// 			animation loop here (if it is independant of interaction with other objects)
// 	4.	collision_check - It doesnt seem possible to handle collision check with a combination
// 			of every object. So as a substitute, just need to provide a function that can check
// 			collision with itself and a rectangle
// 	5.	freeData - a way to free its void * data that it was initialised with


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


