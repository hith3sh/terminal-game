#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node
{
    void* value;
    struct Node* next;
    struct Node* previous;
}Node;

typedef struct LinkedList
{
    Node* head;
    Node* tail;
    int count;

}LinkedList;

LinkedList* Initialize();

void insertLastNode(LinkedList* list, void* value, int valueSize);

void* removeTailNode(LinkedList* list);

void FreeMemory(LinkedList* list);

#endif