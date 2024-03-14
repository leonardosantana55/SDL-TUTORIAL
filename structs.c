#include "main.h"

LinkedList* createLinkedList(Bullet bullet){
    Node* node = malloc(sizeof(Node));
    node->bullet = bullet;
    node->next = NULL;
    
    LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head = node; // point to first
    return ll;

}

void insert_ll(LinkedList* list, Bullet bullet){
    
    //create second node
    Node* node = malloc(sizeof(Node));
    node->bullet = bullet;
    node->next = NULL;

    //insert second node
    node->next = list->head; 
    list->head = node;
        
    return;
}

void print_ll(LinkedList* list){
    Node* temp;
    temp = list->head;
    
    int count = 0;
    while (temp != NULL){
        printf("%p\n", temp);
        temp = temp->next;
        count++;
        printf("quantidade %d\n",count);
    }
    
    return;
}

void free_ll(LinkedList* list){
    Node* temp;
    Node* delete;
    temp = list->head;

    while (temp != NULL){
        printf("freeing at address: %p\n", temp);
        delete = temp;
        temp = temp->next;
        free(delete); 
    }

    free(list);

    return;  
}
    