#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List *createList() 
{
    List *list = (List *)malloc(sizeof(list));
    list -> head = NULL;
    list -> tail = 0;
    list -> current = NULL;
    return list;
}

void * firstList(List * list) 
{
    if(!list -> head) return NULL;
    list->current = list-> head;
    return list -> head -> data;
}

void * nextList(List * list) 
{
    if(!list -> current) return NULL;
    list -> current = list -> current -> next;
    
    if(!list -> current) return NULL;

    return list -> current -> data;
}

void * lastList(List * list) 
{
    if(!list -> tail) return NULL;
    list -> current = list -> tail;
    return list -> tail -> data;
}


void * prevList(List * list) 
{
    if(!list -> current) return NULL;
    list -> current = list -> current -> prev;

    if(!list -> current) return NULL;
    return list -> current -> data;
}

void pushFront(List * list, void * data) 
{
    Node* n = createNode(data);
    n -> next = list -> head;
    if(list -> head)
    {
        list -> head -> prev = n;
    }
    list -> head = n;
    n -> prev = NULL;
    list -> tail = n;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    if(!list -> current) return;

    Node *newNode = createNode(data);
    newNode -> prev = list -> current;
    newNode -> next = list -> current -> next;

    if(list -> current -> next)
    {
        list -> current -> next ->prev = newNode;
    } 
    else 
    {
        list -> tail = newNode;
    }
    list -> current -> next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    if(!list -> current) return NULL;

    void *data = list -> current -> data;
    Node  *prevNode = list -> current -> prev;
    Node  *nextNode = list -> current -> next;

    if(prevNode)
    {
        prevNode -> next = nextNode;
    }
    else
    {
        list -> head = nextNode;
    }

    if(nextNode)
    {
        nextNode -> prev = prevNode;
    }
    else
    {
        list -> tail = prevNode;
    }

    free(list -> current);
    list -> current = nextNode;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}