#ifndef OBJ_H
#define OBJ_H

#include "game.h"

typedef struct object* Object;
typedef struct ListRep* List;

struct object {
	SDL_Rect colBox;
	SDL_Texture* tex;
	SDL_Renderer* rend;
	void* data;

	void (*event_handle) (Object, SDL_Event*, const unsigned char*);
	void (*update_object) (Object, List*);
	void (*render_object) (Object, SDL_Renderer*);
	int (*collision_check) (Object, SDL_Rect*);

	void (*freeData) (void*);

	Object next;
	Object prev;
};

struct ListRep {
	int nitems;
	Object head;
	Object tail;
};

List createList(void);
void freeList(List* l);

void addToList(List l, Object o);
void deleteFromList(List, Object);

Object createObject(SDL_Texture* tex, SDL_Renderer* rend,
					void (*event_handle)(Object, SDL_Event*, const unsigned char*), 
					void (*update_object)(Object, List*), 
					void (*render_object)(Object, SDL_Renderer*),
					int  (*collision_check)(Object, SDL_Rect*),
					void (*freeData)(void*));

void freeObject(Object o);

int check_rect(SDL_Rect*, SDL_Rect*);

#endif


