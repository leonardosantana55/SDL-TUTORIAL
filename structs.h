#ifndef APP_H
#define APP_H

#include "main.h"

typedef struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int rigth;
    int fire;
}App;

typedef struct Bullet{
    SDL_Rect form;
    int dx;
    int dy;
    int distance;
    int health;
    size_t size;
}Bullet;

//define data structures for linkedlist
typedef struct Node{
    Bullet bullet;
    struct Node* next;
}Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
}LinkedList;

//define helper functions
LinkedList* createLinkedList(Bullet bullet);
void insert_ll(LinkedList* list, Bullet bullet);
void print_ll(LinkedList* list);
void free_ll(LinkedList* list);

#endif