#include "../Helper/linkedList.h"
#include "jobs.h"

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
            logStdError("Incorrect argument");
            return;
        }
    }
    else if (argc)
    {
        logStdError("Too many argumentsn");
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
            logStdError("Process doesn't exist");
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
