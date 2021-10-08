#include "../Helper/stringToNum.h"
#include "../Helper/linkedList.h"
#include "../headers.h"
#include "bg.h"

void bg(char** argv, int argc)
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

    kill(node->id, SIGCONT);
    return;
}
