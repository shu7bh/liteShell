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
    searchAndDeleteProcess(temp, node->id);

    int mainPID = getpgrp();

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, node->id);
    kill(node->id, SIGCONT);
    int status;
    waitpid(node->id, &status, WUNTRACED);

    tcsetpgrp(STDIN_FILENO, mainPID);

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return;
}
