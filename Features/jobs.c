#include "jobs.h"
#include "../Helper/linkedList.h"

void jobs(char** argv, int argc)
{
    Node* node = getHead()->next;

    int flag = 0;
    if (argc == 1)
    {
        if (!strcmp(argv[1], "-r"))
            flag = 1;
        else if (!strcmp(argv[1], "-s"))
            flag = -1;
        else
        {
            printf("Incorrect argument\n");
            return;
        }
    }
    else if (argc)
    {
        printf("Too many arguments\n");
        return;
    }

    while (node)
    {
        char filepath[SIZE];
        sprintf(filepath, "/proc/%d/stat", node->id);

        FILE* fp;
        fp = fopen(filepath, "r");

        if (!fp)
        {
            printf("Process doesn't exist\n");
            return;
        }

        char str[SIZE];

        for (int i = 0; i < 3; ++i)
            fscanf(fp, "%s", str);

        char* value = !strcmp(str, "T")? "Stopped" : "Running";

        if (!flag || (flag == 1 && !strcmp(value, "Running")) || (flag == -1 && !strcmp(value, "Stopped")))
            printf("[%d] %s %s [%d]\n", node->num, value, node->command, node->id);
        node = node->next;
    }
}