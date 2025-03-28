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

List * createList() {
    List* lista = (List*) malloc (sizeof(List)) ;
    lista -> head = NULL ;
    lista -> tail = NULL ;
    lista -> current = NULL ;
    return lista ;
}

void * firstList(List * list) {
    list -> current = list -> head ;
    if (list -> current) return list -> current -> data ;
    else return NULL ;
}

void * nextList(List * list) {
    if (list -> current != NULL)
        list -> current = list -> current -> next ;
    if (list -> current != NULL)
        return list -> current -> data ;
    else return NULL ;
}

void * lastList(List * list) {
    if (list -> current == NULL || list -> tail == NULL)
        return NULL ;
    list -> current = list -> tail ;
    return list -> current -> data ;
}

void * prevList(List * list) {
    if(list -> current != NULL)
        list -> current = list -> current -> prev ;
    if (list -> current != NULL)
        return list -> current -> data ;
    else return NULL ;
}

void pushFront(List * list, void * data) {
    if (list == NULL) return;

    Node * newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->data = data;
    newNode->next = list->head; 
    newNode->prev = NULL;

    if (list->head != NULL) {
        list->head->prev = newNode;
    }
    list->head = newNode;

    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return; 

    Node * newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return;

    newNode->data = data;

    if (list == NULL || list->current == NULL) return; // Verifica que la lista y current sean válidos

    Node * newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return; // Verifica si la asignación de memoria fue exitosa

    newNode->data = data;

    // **Caso 1: current está en tail → actualizar tail**
    if (list->current == list->tail) {
        newNode->prev = list->tail;
        newNode->next = NULL;

        if (list->tail != NULL) {
            list->tail->next = newNode;
        }

        list->tail = newNode; // **Nuevo nodo es ahora el último**
        return;
    }

    // **Caso 2: current está en el medio o al inicio**
    newNode->next = list->current;
    newNode->prev = list->current->prev;

    if (list->current->prev != NULL) {
        list->current->prev->next = newNode;
    }

    list->current->prev = newNode;

    // **Caso especial: si current estaba en head, actualizar head**
    if (list->current == list->head) {
        list->head = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}