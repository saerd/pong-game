#include "game.h"

Object createObject(SDL_Texture* tex, void (*event_handle)(Object, SDL_Event*, const unsigned char*), void (*update_object)(Object)){
	Object obj = malloc(sizeof(struct object));
	obj->tex = tex;
	obj->event_handle = event_handle;
	obj->update_object = update_object;
}

void renderObject(Object obj, SDL_Renderer *rend){
	SDL_RenderCopy(rend, obj->tex, NULL, &obj->colBox);
}




