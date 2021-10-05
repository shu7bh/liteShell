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
    strcpy(fgDetails.args, node->command);
    strcpy(fgDetails.command, node->name);

    searchAndDeleteProcess(temp, node->id);

    int mainPID = getpgrp();

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, node->id);
    kill(node->id, SIGCONT);
    int status;
    waitpid(node->id, &status, 0);
    printf("%d", node->id);

    tcsetpgrp(STDIN_FILENO, mainPID);

    fgDetails.pid = -1;
    memset(fgDetails.command, 0, SIZE);
    memset(fgDetails.args, 0, SIZE);

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return;
}
