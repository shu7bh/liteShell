#include "cd.h"
#include "homeDir.h"
#include "headers.h"

int cd(char* argv)
{
    char prevDir[1000];
    char temp[1000];

    getcwd(temp, 1000);
    if (!strcmp(argv, "") || !strcmp(argv, "~"))
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
