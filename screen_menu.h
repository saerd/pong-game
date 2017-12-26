#ifndef S_MENU_H
#define S_MENU_H

#include "screens.h"

typedef struct menuRep* Menu;

struct menuRep {
	List buttons;
};

Screen createMenuScreen(SDL_Window* window, SDL_Renderer* rend);
void updateMenuScreen(Screen s, Input in, List screens);
void renderMenuScreen(Screen s);
void freeMenuScreen(Screen s);

int startGameAction(Object o, List screens);
int backAction(Object o, List screens);

#endif
