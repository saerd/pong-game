#include "List.h"

List createList(void (*free_item)(void*), void (*assign_parent)(void*, Node)){
	List l = malloc(sizeof(struct listRep));

	l->head = NULL;
	l->tail = NULL;
	l->free_item = free_item;
	l->assign_parent = assign_parent;

	return l;
}

void freeList(List l){
	Node c = l->head;
	Node p;
	while(c){
		p = c;
		c = c->next;
		deleteFromList(l, p);
	}
	free(l);
}

Node createNode(void* item){
	Node n = malloc(sizeof(struct node));

	n->item = item;
	n->next = NULL;
	n->prev = NULL;

	return n;
}
void addToList(List l, void* item){
	Node n = createNode(item);
	l->assign_parent(item, n);

	if(!l){
		return;
	}
	if(l->tail){
		l->tail->next = n;
		n->prev = l->tail;
	}
	if(!l->head){
		l->head = n;
	}
	l->tail = n;

}

void deleteFromList(List l, Node n){
	if(!l || !n){
		return;
	}

	if(n->prev){
		n->prev->next = n->next; 
	}
	else{
		l->head = l->head->next;
	}

	if(n->next){
		n->next->prev = n->prev;
	}
	else{
		l->tail = l->tail->prev;
	}

	l->free_item(n->item);
	free(n);
}
