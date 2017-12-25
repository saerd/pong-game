#ifndef LIST_H
#define LIST_H

#include "stdlib.h"
#include "stdio.h"

typedef struct listRep* List;
typedef struct node* Node;

struct listRep {
	Node head;
	Node tail;

	void (*free_item)(void*);
	void (*assign_parent)(void*, Node);
};

struct node {
	void *item;
	Node next;
	Node prev;
};

List createList(void (*free_item)(void*), void (*assign_parent)(void*, Node));
void freeList(List l);

Node createNode(void*);
void addToList(List, void*);
void deleteFromList(List, Node);
#endif
