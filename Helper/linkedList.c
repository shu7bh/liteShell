#include "linkedList.h"
#include "../headers.h"

Node* head;
Node* createProcess();
int num = 0;

void makeProcessLinkedList()
{
    head = createProcess();
}

void addProcess(char* name, char** command, int id)
{
    Node* node = createProcess();

    char str[SIZE] = {0};

    for (int i = 0; command[i]; ++i)
        strcat(str, command[i]), strcat(str, " ");
    str[strlen(str) - 1] = 0;

    strcpy(node->name, name);
    strcpy(node->command, str);
    node->id = id;
    node->num = ++num;

    Node* temp = head;

    while (temp->next)
        if (strcmp(temp->next->command, str) > 0 || (!strcmp(temp->next->command, str) && temp->next->id > id))
        {
            node->next = temp->next;
            temp->next = node;
            return;
        }
        else
            temp = temp->next;

    node->next = temp->next;
    temp->next = node;
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

    memset(node->name, 0, SIZE);
    memset(node->command, 0, SIZE);
    node->id = 0;
    node->next = 0;

    return node;
}

Node* getHead()
{
    return head;
}

Node* getNodeNum(int num)
{
    Node* node = head->next;

    while (node)
        if (node->num == num)
            return node;
        else
            node = node->next;

    return 0;
}
