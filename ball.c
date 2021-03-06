#include "ball.h"

Object createBall(SDL_Renderer* rend){
	Object b;

	SDL_Surface* surface = IMG_Load("art/ball.png");
//	SDL_Surface* surface = SDL_CreateRGBSurface(0, side, side, 32, 0, 0, 0, 0);
//	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	if(!surface){
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		return NULL;	
	}

	b = createObject(tex, rend, ball_EH, ball_update, ball_render, ball_col_check, free_ball);	
	Ball d = malloc(sizeof(struct ball));
	d->rise = (rand() % 2 == 1) ? 1: -1;
	d->run = (rand() % 2 == 1) ? 1: -1;
	d->current_sprite = 0;
	d->done = 0;

	b->data = d;

	int side = 20;
	b->colBox.x = (WIN_WIDTH - side/2) /2;
	b->colBox.y = (WIN_HEIGHT - side/2) /2;
	b->colBox.w = side;
	b->colBox.h = side;

	return b;
}

int ball_EH(Object b, Input in, List screens){
	Ball d = b->data;
	if(0 && d->done){
		Screen current = screens->tail->item;
		Screen new = createMenuScreen(current->window, current->rend);
		addToList(screens, new);
//		deleteFromList(screens, current->parent);
		return 0;
	}
	return 1;
}

void ball_update(Object b, List *objList){
	Ball d = b->data;
	if(b->colBox.x + b->colBox.w >= WIN_WIDTH || b->colBox.x <= 0){
		reverseBall(d, RUN);
	}
	if(b->colBox.y + b->colBox.h >= WIN_HEIGHT || b->colBox.y <= 0){
		reverseBall(d, RISE);
		d->done = 1;
	}
	Node c = objList[PLAYERS]->head;
	Object obj = NULL;
	while(c){
		obj = (Object) c->item;
		if(obj->collision_check(obj, &b->colBox)){
			/*
			int p_int = obj->colBox.x + (obj->colBox.w / 2);
			int b_int = b->colBox.x + (b->colBox.w / 2);
			double norm_int = (b_int - p_int) / ((double)obj->colBox.w / 2);
			double bounce_angle = norm_int * (5 * 3.1415/12);
			printf("%lf %lf\n", 2 * cos(bounce_angle), 2 * sin(bounce_angle));
			*/
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
			break;
		}
		c = c->next;
	}
	
	if(!c){
		b->colBox.y += d->rise;
		b->colBox.x += d->run;
		return;
	}
	while(obj && obj->collision_check(obj, &b->colBox)){
		b->colBox.y += d->rise;
		/*
		printf("----\n");
		printf("height is %d\n", b->colBox.y);
		printf("rise is %d\n", d->rise);
		printf("orginal is %d\n", orig);
		printf("changed %d times\n", change);
		printf("----\n");
		*/
	}
	b->colBox.x += d->run;
}

void ball_render(Object b, SDL_Renderer* rend){
	SDL_Rect* r = &b->colBox;
	int w, h;
	SDL_QueryTexture(b->tex, NULL, NULL, &w, &h);
	w /= 4;
	h /= 4;

	int repeat = 40;

	Ball d = b->data;
	int c = d->current_sprite / repeat;

	int x = (c / 4) * w, y = (c % 4) * h;
	SDL_Rect src = {x, y, w, h};

	int offset = r->w / 3;
	SDL_Rect dest = {r->x - offset, r->y - offset, r->w + 2 * offset, r->h + 2 * offset};

	/*
	double angle = atan(abs(d->rise) / abs(d->run)) * 180/3.14;
	if(d->rise < 0 && d->run < 0){
		angle += 180;
	}
	else if(d->rise < 0 && d->run >= 0){
		angle = -angle;
	}
	else if(d->rise > 0 && d->run <= 0){
		angle = -angle + 180;
	}
	*/
	SDL_RenderCopy(rend, b->tex, &src, &dest);

	d->current_sprite = (d->current_sprite + 1) % (16 * repeat);
}

int ball_col_check(Object b, SDL_Rect* r){
	return check_rect(&b->colBox, r);
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

void free_ball(void * b){
	free(b);
}


