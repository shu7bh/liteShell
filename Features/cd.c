#include "../Helper/homeDir.h"
#include "../headers.h"
#include "cd.h"

void cd(char** argv, int argc)
{
    static char prevDir[1000];

    if (argc > 1)
    {
        logStdError("Too many arguments");
        return;
    }

    static int ct = 0;
    if (!ct++)
        strcpy(prevDir, getHomeDir());

    char temp[1000];
    getcwd(temp, 1000);

    if (!argv[1] || !strcmp(argv[1], "~"))
        chdir(getHomeDir());
    else if (!strcmp(argv[1], "-"))
    {
        printf("%s\n", prevDir);
        chdir(prevDir);
    }
    else if (chdir(argv[1]))
    {
        logError("chdir error");
        return;
    }

    strcpy(prevDir, temp);
    return;
}
