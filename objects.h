#ifndef OBJ_H
#define OBJ_H

#include "game.h"

typedef struct object* Object;
typedef struct ListRep* List;

struct object {
	SDL_Rect colBox;
	SDL_Texture* tex;
	void* data;

	void (*event_handle) (Object, SDL_Event*, const unsigned char*);
	void (*update_object) (Object, List);
	void (*render_object) (Object, SDL_Renderer*);
	int (*collision_check) (Object, SDL_Rect*);

	void (*freeData) (void*);

	Object next;
};

struct ListRep {
	int nitems;
	Object head;
	Object tail;
};

List createList(void);
void freeList(List l);

void addToList(List l, Object o);

Object createObject(SDL_Texture* tex, 
					void (*event_handle)(Object, SDL_Event*, const unsigned char*), 
					void (*update_object)(Object, List), 
					void (*render_object)(Object, SDL_Renderer*),
					int  (*collision_check)(Object, SDL_Rect*),
					void (*freeData)(void*));

int check_rect(SDL_Rect*, SDL_Rect*);

#endif


