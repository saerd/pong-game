#include "game.h"

List createList(void){
	List l = malloc(sizeof(struct ListRep));
	l->head = NULL;
	l->tail = NULL;
	l->nitems = 0;

	return l;
}

void freeList(List l){
	Object c = l->head;
	Object p;
	while(c){
		p = c;
		c = c->next;
		free(p);
	}
	free(l);
}

void addToList(List l, Object o){
	if(!l){
		return;
	}
	if(l->tail){
		l->tail->next = o;
	}
	if(!l->head){
		l->head = o;
	}
	l->tail = o;
}

Object createObject(SDL_Texture* tex, 
					void (*event_handle)(Object, SDL_Event*, const unsigned char*), 
					void (*update_object)(Object, List), 
					void (*render_object)(Object, SDL_Renderer*),
					void (*freeData)(void *))
{
	Object obj = malloc(sizeof(struct object));

	obj->tex = tex;
	obj->event_handle = event_handle;
	obj->update_object = update_object;
	obj->render_object = render_object;

	obj->freeData = freeData;
	obj->next = NULL;
}

void freeObject(Object o){
	SDL_DestroyTexture(o->tex);
	o->freeData(o->data);
	free(o);
}

int checkCollision(Object a, Object b){
	int leftA = a->colBox.x, 			leftB = b->colBox.x;
	int rightA = leftA + a->colBox.w, 	rightB = leftB + b->colBox.w;
	int topA = a->colBox.y, 			topB = b->colBox.y;
	int botA = topA + a->colBox.h,		botB = topB + b->colBox.h;

	if(botA <= topB) return 0;
	if(topA >= botB) return 0;
	if(leftA >= rightB) return 0;
	if(rightA <= leftB) return 0;

	/*
	printf("BOT: |%d - %d| = %d\n", botA, topB, abs(botA - topB));
	printf("TOP: |%d - %d| = %d\n", topA, botB, abs(topA - botB));
	printf("LEFT: |%d - %d| = %d\n", leftA, rightB, abs(leftA - rightB));
	printf("RIGHT: |%d - %d| = %d\n", rightA, leftB, abs(rightA - leftB));
	printf("\n");
	*/
	printf("%d %d %d %d\n", leftA, topA, a->colBox.w, a->colBox.h);
	printf("%d %d %d %d\n", leftB, topB, b->colBox.w, b->colBox.h);
	return 1;
}





