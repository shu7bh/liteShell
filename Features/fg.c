#include "../Helper/stringToNum.h"
#include "../Helper/linkedList.h"
#include "../headers.h"
#include "fg.h"

void fg(char** argv, int argc)
{
    if (!argc || argc > 1)
    {
        logStdError("1 argument required");
        return;
    }

    int jobNumber = stringToNum(argv[1]);
    Node* node = getNodeNum(jobNumber);

    if (!node)
    {
        logStdError("Job doesn't exist");
        return;
    }

    int pid = node->id;

    if (kill(pid, SIGCONT))
    {
        logError("kill error");
        return;
    }

    char temp[SIZE];
    char name[SIZE], com[SIZE];
    strcpy(name, node->name);
    strcpy(com, node->command);

    searchAndDeleteProcess(temp, pid);

    int status;
    if (waitpid(pid, &status, WUNTRACED) == -1)
        logError("waitpid error");

    if (WIFSTOPPED(status))
    {
        printf("\r");
        kill(pid, SIGTSTP);
        char* command[2];
        command[0] = strdup(com);
        command[1] = 0;

        addProcess(name, command, pid);
        free(command[0]);
    }

    /*clearFg();*/
    return;
}

