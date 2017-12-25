#ifndef BUTTON_H
#define BUTTON_H

#include "game.h"

typedef struct button* Button;

struct button {
	int pressed;
	int trigger;
};

Object createButton(int x, int y, int w, int h, SDL_Renderer* rend);
void button_EH(Object b, SDL_Event *e, const unsigned char * key_states, List screens);
void button_update(Object b, List*);
void button_render(Object, SDL_Renderer*);
int button_col_check(Object b, SDL_Rect* r);

void free_button(void * b);

#endif
