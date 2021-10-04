#include "linkedList.h"
#include "headers.h"

Node* head;
Node* createProcess();

void makeProcessLinkedList()
{
    head = createProcess();
}

void addProcess(char* name, int id)
{
    Node* node = createProcess();

    strcpy(node->name, name);
    node->id = id;
    node->next = head->next;

    head->next = node;
}

int searchAndDeleteProcess(char* name, int id)
{
    Node* node = head;

    while (node->next)
    {
        if (node->next->id == id)
        {
            Node* temp = node->next;
            strcpy(name, temp->name);
            node->next = temp->next;
            free(temp);
            return 1;
        }
        node = node->next;
    }
    return 0;
}

Node* createProcess()
{
    Node* node = malloc(sizeof(Node));

    node->name[0] = 0;
    node->id = 0;
    node->next = 0;

    return node;
}
