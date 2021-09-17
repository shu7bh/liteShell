#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

struct Node
{
    char name[100];
    int id;
    Node* next;
};

void makeProcessLinkedList();
void addProcess(char* name, int id);
int searchAndDeleteProcess(char* name, int id);

#endif
