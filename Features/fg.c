#include "../Helper/stringToNum.h"
#include "../Helper/linkedList.h"
#include "../headers.h"
#include "fg.h"

Fg fgDetails;

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

    char temp[SIZE];
    fgDetails.pid = node->id;
    strcpy(fgDetails.command, node->command);
    strcpy(fgDetails.name, node->name);

    if (kill(node->id, SIGCONT))
    {
        logError("kill error");
        return;
    }

    searchAndDeleteProcess(temp, node->id);

    int status;
    if (waitpid(node->id, &status, WUNTRACED) == -1)
        logError("waitpid error");

    clearFg();
    return;
}

void clearFg()
{
    fgDetails.pid = -1;
    memset(fgDetails.name, 0, SIZE);
    memset(fgDetails.command, 0, SIZE);
}

void addFgAr(int pid, char** command)
{
    if (!command[0])
    {
        logStdError("No command");
        return;
    }

    char str[SIZE] = {0};
    for (int i = 0; command[i]; ++i)
        strcat(str, command[i]), strcat(str, " ");

    str[strlen(str) - 1] = 0;

    addFg(pid, command[0], str);
}

void addFg(int pid, char* name, char* command)
{
    clearFg();

    strcpy(fgDetails.command, command);
    fgDetails.pid = pid;
    strcpy(fgDetails.name, name);
}
