#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../headers.h"

typedef struct Node Node;

struct Node
{
    char name[SIZE];
    char command[SIZE];
    int id;
    int num;
    Node* next;
};

// Makes the linked list
void makeProcessLinkedList();

// Adds a process to the linked list
void addProcess(char*, char**, int);

// Searches and deletes a process based on the pid
int searchAndDeleteProcess(char*, int);

// Gets the node based on the job number
Node* getNodeNum(int);

// Gets the head of the linked list
Node* getHead();

#endif
