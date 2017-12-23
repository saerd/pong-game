#include "bullet.h"

Object createBullet(SDL_Renderer* rend){
	Object b;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 255, 0));

	if(!surface){
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;
	}

	b=createObject(tex, rend, bullet_EH, bullet_update, bullet_render, bullet_col_check, free_bullet);
	Bullet d = malloc(sizeof(struct bullet));
	d->current_sprite = 0;
	d->direction = UP;

	b->data = d;

	b->colBox.w = 10;
	b->colBox.h = 10;
	
	return b;
}

void bullet_EH(Object b, SDL_Event *e, const unsigned char * key_states){
	return;
}

void bullet_render(Object b, SDL_Renderer* rend){
	SDL_RenderCopy(rend, b->tex, NULL, &b->colBox);
}

int bullet_col_check(Object b, SDL_Rect* r){
	return 0;
}

void bullet_update(Object b, List* l){
	if(b->colBox.y < 0 || b->colBox.y > WIN_HEIGHT){
		deleteFromList(l[BULLETS], b);
		return;
	}
	Bullet d = b->data;	
	if(d->direction == UP){
		b->colBox.y--;
	}	
	else{
		b->colBox.y++;
	}
}

void free_bullet(void * b){
	free(b);
}
