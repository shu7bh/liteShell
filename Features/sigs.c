#include "../Helper/stringToNum.h"
#include "../Helper/linkedList.h"
#include "../headers.h"
#include "sigs.h"

void sig(char** argv, int argc)
{
    if (argc > 2)
    {
        logStdError("Too many arguments");
        return;
    }
    else if (argc < 2)
    {
        logStdError("Too less arguments");
        return;
    }

    int jobNumber = stringToNum(argv[1]);

    if (jobNumber < 1)
        return;

    int sig = stringToNum(argv[2]);
    if (sig < 1)
        return;

    Node* node = getNodeNum(jobNumber);

    if (node)
    {
        if (kill(node->id, sig) < 0)
            logError("Kill error");
                return;
    }

    logStdError("Job doesn't exist");
}
