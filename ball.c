#include "ball.h"

Object createBall(SDL_Renderer* rend){
	Object b;

	int width = 10, height = 10;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	if(!surface){
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;	
	}

	b = createObject(tex, ball_EH, ball_update);	
	Ball d = malloc(sizeof(struct ball));
	d->rise = 1;
	d->run = 1;

	b->data = d;

	b->colBox.x = (WIN_WIDTH - 10) /2;
	b->colBox.y = (WIN_HEIGHT - 10) /2;
	b->colBox.w = 20;
	b->colBox.h = 20;

	return b;
}

void ball_update(Object b){
	b->colBox.x = (b->colBox.x + 1) % WIN_WIDTH;
}

void ball_EH(Object b, SDL_Event *e, const unsigned char * key_states){
	return;
}


