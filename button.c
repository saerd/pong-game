#include "button.h"

Object createButton(int x, int y, int w, int h,
					int (*action)(Object, List), SDL_Renderer* rend){
	Object b;

	SDL_Surface* surface = IMG_Load("art/button.png");
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

	b = createObject(tex, rend, button_EH, button_update, button_render, button_col_check, free_button);	

	Button new_button = malloc(sizeof(struct button));
	new_button->pressed = 0;
	new_button->trigger = 0;
	new_button->action = action;

	b->data = new_button;

	b->colBox.x = x;
	b->colBox.y = y;
	b->colBox.w = w;
	b->colBox.h = h;

	return b;
}

int button_EH(Object b, Input in, List screens){

	Button d = b->data;
	int x = in->mouse_x, y = in->mouse_y;

	if(in->mask & SDL_BUTTON(SDL_BUTTON_LEFT)){
		if(b->colBox.x < x && x < b->colBox.x + b->colBox.w &&
		   b->colBox.y < y && y < b->colBox.y + b->colBox.h){
			if(!d->pressed){
				d->pressed = PRESSED;
			}
		}
		else{
			d->pressed = HELD;
		}
	}
	else{
		if(b->colBox.x < x && x < b->colBox.x + b->colBox.w &&
		   b->colBox.y < y && y < b->colBox.y + b->colBox.h && d->pressed == PRESSED){
			d->pressed = 0;
			d->trigger = 1;
			return d->action(b, screens);
		}
		else {
			d->pressed = 0;
			d->trigger = 0;
		}
	}

	return 1;
}

void button_update(Object b, List* objList){
	Button d = b->data;
	if(d->trigger){
		printf("triggered\n");
		d->trigger = 0;
	}

}

void button_render(Object b, SDL_Renderer* rend){
	int w, h;
	SDL_QueryTexture(b->tex, NULL, NULL, &w, &h);
	h /= 2;

	SDL_Rect r = {0, 0, w, h};
	Button d = b->data;
	if(d->pressed == PRESSED){
		r.y = h;
	}

	SDL_RenderCopy(rend, b->tex, &r, &b->colBox);

}

int button_col_check(Object b, SDL_Rect* r){
	return 0;
}

void free_button(void * b){
	free(b);
}
