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

void makeProcessLinkedList();
void addProcess(char* name, char** command, int id);
int searchAndDeleteProcess(char* name, int id);
Node* getNodeNum(int num);
Node* getHead();

#endif
