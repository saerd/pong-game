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

	surface = IMG_Load("art/flame_sprite.png");
	if(!surface) return NULL;
	SDL_Texture* bullet_tex = SDL_CreateTextureFromSurface(rend, surface);
	if(!tex) return NULL;

	p = createObject(tex, rend, player_EH, player_update, player_render, player_col_check, free_player);
	Player d = malloc(sizeof(struct player));
	d->moving = 0;
	d->direction = 0;

	d->shoot = NONE;
	d->reload = 0;
	d->restock = RESTOCK_TIME;

	d->n_bullets = MAX_BULLETS;

	d->bullet_tex = bullet_tex;

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

int player_EH(Object p, Input in, List screens){
		
		Player d = (Player) p->data;
		int left = d->left_button, right = d->right_button, shoot = d->shoot_button;

//		SDL_Event* e = in->event;
		const unsigned char* key_states = in->key_states;

		if(key_states[left]){
			d->moving = 1;
			d->direction = left;
		}
		if(key_states[right]){
			d->moving = 1;
			d->direction = right;
		}
		if(key_states[shoot]){
			if(d->reload == 0 && d->n_bullets > 0){
				if(shoot == P1_SHOOT) d->shoot = UP;
				else d->shoot = DOWN;
			}
		}

		if(!key_states[left] && !key_states[right]){
			d->moving = 0;
		}

		return 1;
}

void player_update(Object p, List* objList){
	Player d = p->data;
	SDL_Rect* r = &p->colBox;
	const int left = d->left_button, right = d->right_button;

	if(d->restock >= RESTOCK_TIME){
		d->n_bullets = min(d->n_bullets + 1, MAX_BULLETS);
		d->restock = 0;
	}
	d->restock = min(d->restock + 1, RESTOCK_TIME);
	d->reload = max(d->reload - 1, 0);

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
		Object b = createBullet(x, y, d->bullet_tex, p->rend);
		Bullet bull = b->data;
		bull->direction = d->shoot;
		d->shoot = NONE;
		addToList(objList[BULLETS], b);

		d->reload = RELOAD_TIME;
		d->n_bullets = max(d->n_bullets - 1, 0);
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
	Player pl = p;
	SDL_DestroyTexture(pl->bullet_tex);
	free(p);
}
