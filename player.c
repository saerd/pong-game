#include "player.h"

Object createPlayer(int pNum, SDL_Renderer* rend){
	Object p;

	int width = 10, height = 10;
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 255));
	if(!surface){
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;	
	}

	p = createObject(tex, player_EH, player_update);	
	Player d = malloc(sizeof(struct player));
	d->moving = 0;
	d->direction = 0;

	p->data = d;

	p->colBox.x = (WIN_WIDTH - 50) /2;
	p->colBox.y = WIN_HEIGHT - (WIN_HEIGHT /15);
	p->colBox.w = 100;
	p->colBox.h = 20;

	return p;
}

void player_EH(Object p, SDL_Event *e, const unsigned char * key_states){
		Player d = (Player) p->data;
		if(key_states[LEFT]){
			d->moving = 1;
			d->direction = LEFT;
		}
		if(key_states[RIGHT]){
			d->moving = 1;
			d->direction = RIGHT;
		}
		if(e->type == SDL_KEYDOWN){
			if(e->key.keysym.sym == SDLK_LEFT){
				d->moving = 1;
				d->direction = LEFT;
			}
			if (e->key.keysym.sym == SDLK_RIGHT){
				d->moving = 1;
				d->direction = RIGHT;
			}
		}

		if(!key_states[LEFT] && !key_states[RIGHT]){
			d->moving = 0;
		}
}

void player_update(Object p){
	Player d = p->data;
	SDL_Rect* r = &p->colBox;
	if(d->moving){
		switch(d->direction) {
			case LEFT :
				r->x = max(r->x - 2, 0);
				break;

			case RIGHT :
				r->x = min(r->x + 2, WIN_WIDTH - r->w);
				break;
		}
	}
	
}
