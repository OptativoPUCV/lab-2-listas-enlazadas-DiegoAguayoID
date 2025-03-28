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
    if (list == NULL) return; // Verifica si la lista está inicializada

    Node * newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return; // Verifica si se asignó memoria correctamente

    newNode->data = data;
    newNode->next = list->head; // El nuevo nodo apunta a la antigua cabeza
    newNode->prev = NULL;       // Como es el primero, no tiene nodo anterior

    if (list->head != NULL) {
        list->head->prev = newNode; // El antiguo primer nodo ahora apunta atrás al nuevo nodo
    }

    list->head = newNode; // La cabeza de la lista ahora es el nuevo nodo

    if (list->tail == NULL) { // Si la lista estaba vacía, también actualiza tail
        list->tail = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) return; // Verifica si la lista está inicializada y si current es válido

    Node * newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return; // Verifica si la asignación de memoria fue exitosa

    newNode->data = data;

    // Caso especial: si `current` está en `head`, es equivalente a `pushFront`
    if (list->current == list->head) {
        newNode->next = list->head;
        newNode->prev = NULL;

        if (list->head != NULL) {
            list->head->prev = newNode;
        }

        list->head = newNode; // Actualiza la cabeza de la lista
        return;
    }

    // Caso general: insertar antes de `current`
    newNode->next = list->current;
    newNode->prev = list->current->prev;

    if (list->current->prev != NULL) {
        list->current->prev->next = newNode;
    }

    list->current->prev = newNode;
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