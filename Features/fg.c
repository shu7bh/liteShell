#include "fg.h"
#include "../headers.h"
#include "../Helper/linkedList.h"
#include "../Helper/stringToNum.h"

void fg(char** argv, int argc)
{
    if (!argc || argc > 1)
    {
        printf("1 argument required\n");
        return;
    }

    int jobNumber = stringToNum(argv[1]);
    Node* node = getNodeNum(jobNumber);

    if (!node)
    {
        printf("Job doesn't exist\n");
        return;
    }

    char temp[SIZE];
    fgDetails.pid = node->id;
    strcpy(fgDetails.command, node->command);
    strcpy(fgDetails.name, node->name);

    searchAndDeleteProcess(temp, node->id);

    int mainPID = getpgrp();

    kill(node->id, SIGCONT);
    int status;

    if (waitpid(node->id, &status, WUNTRACED) == -1)
        perror("waitpid error");

    fgDetails.pid = -1;
    memset(fgDetails.name, 0, SIZE);
    memset(fgDetails.command, 0, SIZE);

    return;
}
