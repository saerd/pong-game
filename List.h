#ifndef LIST_H
#define LIST_H

#include "stdlib.h"
#include "stdio.h"

// Generic list implementation designed only to store data of one specific type
// must be initialised with a function to free this data and a function
// to have its container Node be referencable from within the data
// this is so that an item can delete itself from the list only when added to a list

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
