#include "screen_menu.h"

Screen createMenuScreen(SDL_Window* window, SDL_Renderer* rend){
	int height = 150, width = 320;
	Object b1 = createButton((WIN_WIDTH - width)/2, (WIN_HEIGHT - height)/2, width, height, backAction, rend);
	Object b2 = createButton(10, 10, width, height, startGameAction, rend);

	List buttons = createList(freeObject, object_parent);

	addToList(buttons, b1);
	addToList(buttons, b2);

	Menu m = malloc(sizeof(*m));

	m->buttons = buttons;

	Screen s = createScreen(m, window, rend, updateMenuScreen, renderMenuScreen, freeMenuScreen);
	return s;

}

void updateMenuScreen(Screen s, Input in, List screens){

	Menu m = s->screen_data;
	List buttons = m->buttons;

	Node c = buttons->head, n = NULL;
	while(c){
		n = c->next;
		Object o = c->item;
		if(!o->event_handle(o, in, screens)) return;
		o->update_object(o, &buttons);
		c = n;
	}
}

void renderMenuScreen(Screen s){
	Menu m = s->screen_data;
	List buttons = m->buttons;
	Node c;
	for(c = buttons->head; c; c = c->next){
		Object o = c->item;
		o->render_object(o, s->rend);
	}
}

void freeMenuScreen(Screen s){
	Menu m = s->screen_data;
	freeList(m->buttons);
	free(m);
	free(s);
}

int startGameAction(Object o, List screens){
	Screen current = screens->tail->item;
	Screen new = createGameScreen(current->window, current->rend);
	addToList(screens, new);
	while(screens->head != new->parent){
		deleteFromList(screens, screens->head);
	}
	return 0;
}

int backAction(Object o, List screens){
	deleteFromList(screens, screens->tail);
	return 0;
}
