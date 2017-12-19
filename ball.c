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

	b = createObject(tex, ball_EH, ball_update, ball_render, free_ball);	
	Ball d = malloc(sizeof(struct ball));
	d->rise = (rand() % 2 == 1) ? 1: -1;
	d->run = (rand() % 2 == 1) ? 1: -1;
	d->done = 0;

	b->data = d;

	b->colBox.x = (WIN_WIDTH - 10) /2;
	b->colBox.y = (WIN_HEIGHT - 10) /2;
	b->colBox.w = 20;
	b->colBox.h = 20;

	return b;
}

void ball_update(Object b, List objList){
	Ball d = b->data;
	if(b->colBox.x + b->colBox.w >= WIN_WIDTH || b->colBox.x <= 0){
		reverseBall(d, RUN);
	}
	if(b->colBox.y + b->colBox.h >= WIN_HEIGHT || b->colBox.y <= 0){
		d->done = 1;
		return;
	}
	Object c = objList->head;
	while(c){
		if(c != b && checkCollision(c, b)){
			reverseBall(d, RISE);
			int r = rand() % 6;
			
			switch(r){
				case 0:
				case 1:
				case 2:
				case 3:
					ballSpeed(d, INCREASE);
					break;
				case 4:
					ballSpeed(d, DECREASE);
			}
		}
		c = c->next;
	}
	
	b->colBox.x = (b->colBox.x + d->run);
	b->colBox.y = (b->colBox.y + d->rise);
}

void ball_render(Object b, SDL_Renderer* rend){
	SDL_RenderCopy(rend, b->tex, NULL, &b->colBox);
}

void ballSpeed(Ball b, int flag){
	int unit = ((b->rise > 0) ? 1: - 1);
	int limit = 3 * unit;
	switch(flag){
		case NORMAL:
			b->rise = unit;
			break;
		case INCREASE:
			b->rise = unit * min(abs(b->rise + unit), abs(limit));
			break;
		case DECREASE:
			b->rise = unit * max(abs(b->rise - unit), abs(unit));
	}
}

void reverseBall(Ball b, int flag){
	switch(flag){
		case RISE:
			b->rise = -(b->rise);
			break;
		case RUN:
			b->run = -(b->run);
			break;
	}
}


void ball_EH(Object b, SDL_Event *e, const unsigned char * key_states){
	return;
}

void free_ball(void * b){
	free(b);
}


