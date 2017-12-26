#ifndef BUTTON_H
#define BUTTON_H

#include "game.h"

typedef struct button* Button;

#define PRESSED 1
#define HELD 2

struct button {
	int pressed;
	int trigger;
	int (*action)(Object, List);
};

Object createButton(int x, int y, int w, int h, 
					int (*action)(Object, List), SDL_Renderer* rend);
int button_EH(Object b, Input in, List screens);
void button_update(Object b, List*);
void button_render(Object, SDL_Renderer*);
int button_col_check(Object b, SDL_Rect* r);

void free_button(void * b);

#endif
