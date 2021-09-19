#include "cd.h"
#include "homeDir.h"
#include "headers.h"

int cd(char* argv)
{
    static char prevDir[1000];

    static int ct = 0;
    if (!ct++)
        strcpy(prevDir, getHomeDir());

    char temp[1000];
    getcwd(temp, 1000);

    if (!argv || !strcmp(argv, "~"))
        chdir(getHomeDir());
    else if (!strcmp(argv, "-"))
    {
        printf("%s\n", prevDir);
        chdir(prevDir);
    }
    else if (chdir(argv))
        return -1;

    strcpy(prevDir, temp);
    return 0;
}
