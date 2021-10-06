#include "bg.h"
#include "../headers.h"
#include "../Helper/linkedList.h"
#include "../Helper/stringToNum.h"

void bg(char** argv, int argc)
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

    kill(node->id, SIGCONT);
    return;
}