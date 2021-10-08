#include "../Helper/stringToNum.h"
#include "../Helper/homeDir.h"
#include "../Helper/token.h"
#include "../headers.h"
#include "pinfo.h"

void pinfo(char** argv, int argc)
{
    int pid = argc ? stringToNum(argv[1]) : getpid();

    if (pid < 1)
        return;

    char filepath[SIZE] = {0};
    sprintf(filepath, "/proc/%d/stat", pid);

    FILE* fp;
    fp = fopen(filepath, "r");

    if (!fp)
    {
        logError("Process doesn't exist");
        return;
    }

    char statString[35][60] = {0};

    for (int i = 0; i < 30; ++i)
        fscanf(fp, "%s", statString[i]);

    int fgFlag = !strcmp(statString[0], statString[7]);

    sprintf(filepath, "/proc/%d/exe", pid);

    char executablepath[SIZE] = {0};
    int len = readlink(filepath, executablepath, sizeof(executablepath));

    char relativePath[SIZE] = {0};

    if (!strcmp(executablepath, getHomeDir()))
        sprintf(relativePath, "~");
    else if (strstr(executablepath, getHomeDir()))
        sprintf(relativePath, "~%s", executablepath + strlen(getHomeDir()));
    else
        sprintf(relativePath, "%s", executablepath);

    printf("pid -- %s\nProcess Status -- %s%s\nmemory -- %s {Virtual Memory}\nExecutable Path -- %s\n", statString[0], statString[2], fgFlag ? "+" : "", statString[22], relativePath);
}
