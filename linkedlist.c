#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

LinkedList* Initialize(){
    LinkedList* Llist = (LinkedList*) calloc(1, sizeof(LinkedList));
    return Llist;
}

/* removes the last node and return its value */
void* removeTailNode(LinkedList* Llist){
    if (Llist->count == 0){
        return NULL;
    } else{
        Node* tempNode;
        void* item;

        tempNode = Llist->tail;
        Llist->tail = tempNode->previous;
        
        Llist->count = Llist->count - 1;
        item = tempNode->value;

        free(tempNode);
        return item;
    }
}

/* creates a new node containing a copy of the data passed in to the function */
void insertLastNode(LinkedList* Llist, void* value, int valueSize)
{
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (Llist->count == 0){
        Llist->head = newNode;
        Llist->tail = newNode;
    }else{
        Llist->tail->next = newNode;
        newNode->previous = Llist->tail;
        Llist->tail = newNode;
    }
    newNode->value = malloc(valueSize);
    Llist->count = Llist->count + 1;
    /* to copy data from value parameter to new node's value parameter */
    memcpy(newNode->value, value, valueSize);
}

void FreeMemory(LinkedList* Llist){
    Node *current, *nextNode;
    current = Llist->head;
    while (current != NULL){
        nextNode = current->next;
        free(current->value);
        free(current);
        current = nextNode;
    }
    
    free(Llist);
}