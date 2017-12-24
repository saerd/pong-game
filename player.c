#include "player.h"

Object createPlayer(int pNum, SDL_Renderer* rend){
	int p_height, p_left, p_right, p_shoot;
	if(pNum == 1){
		p_height = WIN_HEIGHT - (WIN_HEIGHT / 10);
		p_left = P1_LEFT;
		p_right = P1_RIGHT;
		p_shoot = P1_SHOOT;
	}
	else{
		p_height = WIN_HEIGHT /10 - 20;
		p_left = P2_LEFT;
		p_right = P2_RIGHT;
		p_shoot = P2_SHOOT;
	}

	Object p;

	int width = 100, height = 15;
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

	p = createObject(tex, rend, player_EH, player_update, player_render, player_col_check, free_player);
	Player d = malloc(sizeof(struct player));
	d->moving = 0;
	d->direction = 0;
	d->shoot = NONE;

	d->left_button = p_left;
	d->right_button = p_right;
	d->shoot_button = p_shoot;

	p->data = d;

	p->colBox.x = (WIN_WIDTH - width/2) /2;
	p->colBox.y = p_height;
	p->colBox.w = width;
	p->colBox.h = height;

	return p;
}

void player_EH(Object p, SDL_Event *e, const unsigned char * key_states){
		Player d = (Player) p->data;
		int left = d->left_button, right = d->right_button, shoot = d->shoot_button;

		if(key_states[left]){
			d->moving = 1;
			d->direction = left;
		}
		if(key_states[right]){
			d->moving = 1;
			d->direction = right;
		}
		if(e->type == SDL_KEYDOWN){
			if(e->key.keysym.scancode == left){
				d->moving = 1;
				d->direction = left;
			}
			if (e->key.keysym.scancode == right){
				d->moving = 1;
				d->direction = right;
			}
			if (e->key.keysym.scancode == shoot){
				if(shoot == P1_SHOOT) d->shoot = UP;
				else d->shoot = DOWN;

			}
		}

		if(!key_states[left] && !key_states[right]){
			d->moving = 0;
		}
}

void player_update(Object p, List* objList){
	Player d = p->data;
	SDL_Rect* r = &p->colBox;
	const int left = d->left_button, right = d->right_button;

	if(d->moving){
		if(d->direction == left){
			r->x -= 2;
			if(r->x < 0) r->x = WIN_WIDTH;
		}
		else if(d->direction == right){
			r->x += 2;
			if(r->x > WIN_WIDTH) r->x = 0;
		}
	}
	if(d->shoot){
		int x = p->colBox.x + (p->colBox.w - 5)/ 2;
		int y = p->colBox.y;
		Object b = createBullet(x, y, p->rend);
		Bullet bull = b->data;
		bull->direction = d->shoot;
		d->shoot = NONE;
		addToList(objList[BULLETS], b);
	}
}

void player_render(Object p, SDL_Renderer* rend){
	SDL_Rect temp = p->colBox;
	int split = temp.x + temp.w - WIN_WIDTH;
	if(split <= 0){
		SDL_RenderCopy(rend, p->tex, NULL, &temp);
	}
	else{
		temp.w -= split;
		SDL_RenderCopy(rend, p->tex, NULL, &temp);
		temp.x = 0;
		temp.w = split;
		SDL_RenderCopy(rend, p->tex, NULL, &temp);
	}
}

int player_col_check(Object p, SDL_Rect* r){
	SDL_Rect temp = p->colBox;
	int split = temp.x + temp.w - WIN_WIDTH;
	if(split <= 0){
		return check_rect(&temp, r);
	}
	else{
		temp.w -= split;
		if(check_rect(&temp, r)) return 1;
		temp.x = 0;
		temp.w = split;
		if(check_rect(&temp, r)) return 1;
	}
	return 0;
}

void free_player(void* p){
	free(p);
}
