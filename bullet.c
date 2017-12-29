#include "bullet.h"

Object createBullet(int x, int y, SDL_Texture* tex, SDL_Renderer* rend){
	if(!tex || !rend) return NULL;

	Object b;

	b=createObject(NULL, rend, bullet_EH, bullet_update, bullet_render, bullet_col_check, free_bullet);
	Bullet d = malloc(sizeof(struct bullet));
	d->direction = UP;
	d->current_sprite = 0;
	d->change_sprite = 0;
	d->sprite = tex;

	b->data = d;

	b->colBox.x = x;
	b->colBox.y = y;
	b->colBox.w = 10;
	b->colBox.h = 10;
	
	return b;
}

int bullet_EH(Object b, Input in, List screens){
	return 1;
}

void bullet_render(Object b, SDL_Renderer* rend){
	int w, h;
	Bullet d = b->data;
	SDL_QueryTexture(d->sprite, NULL, NULL, &w, &h);
	w /= 6;

	SDL_Rect src = {w * d->current_sprite, 0, w, h};
	SDL_Rect dest = b->colBox;

	int enlarge = 20;
	dest.x -= enlarge;
	dest.y -= enlarge;
	dest.w += 2 * enlarge;
	dest.h += 2 * enlarge;

	float rotation = 90;
	if(d->direction == UP) rotation = -rotation;

	SDL_RenderCopyEx(rend, d->sprite, &src, &dest, rotation, NULL, SDL_FLIP_NONE);
}

int bullet_col_check(Object b, SDL_Rect* r){
	return 0;
}

void bullet_update(Object b, List* l){
	if(b->colBox.y + b->colBox.h < 0 || b->colBox.y > WIN_HEIGHT){
		deleteFromList(l[BULLETS], b->parent);
		return;
	}
	Bullet d = b->data;	
	if(d->direction == UP){
		b->colBox.y -= 2;
	}	
	else{
		b->colBox.y += 2;
	}
	if(d->change_sprite >= CHANGE_TIME){
		d->current_sprite = (d->current_sprite + 1) % ANIMATION_LENGTH;
		d->change_sprite = 0;
	}
	d->change_sprite ++;
}

void free_bullet(void * b){
	free(b);
}
