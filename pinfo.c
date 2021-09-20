#include "pinfo.h"
#include "headers.h"
#include "stringToNum.h"
#include "homeDir.h"
#include "token.h"

void pinfo(int argc, char **argv)
{
    int pid = argc ? stringToNum(argv[1]) : getpid();

    char filepath[512];
    sprintf(filepath, "/proc/%d/stat", pid);

    FILE* fp;
    fp = fopen(filepath, "r");

    if (!fp)
    {
        perror("fopen error");
        return;
    }

    size_t size = SIZE;
    char *string = malloc(size);

    getline(&string, &size, fp);

    char** statString = malloc(55); // As there can be at most 52 tokens
    int ct, temp;
    tokenize(string, statString, &ct, &temp);

    int fgFlag = !strcmp(statString[0], statString[7]);

    sprintf(filepath, "/proc/%d/exe", pid);

    char executablepath[SIZE];
    int len = readlink(filepath, executablepath, sizeof(executablepath));

    if(len == -1)
    {
        strcpy(executablepath, "NULL");
        executablepath[4] = 0;
    }
    else
        executablepath[len] = 0;

    char relativePath[SIZE];

    if (!strcmp(executablepath, getHomeDir()))
        sprintf(relativePath, "~");
    else if (strstr(executablepath, getHomeDir()))
        sprintf(relativePath, "~%s", executablepath + strlen(getHomeDir()));
    else
        sprintf(relativePath, "%s", executablepath);

    printf("pid -- %s\nProcess Status -- %s%s\nmemory -- %s {Virtual Memory}\nExecutable Path -- %s\n", statString[0], statString[2], fgFlag ? "+" : "", statString[22], relativePath);

    for (int i = 0; statString[i]; ++i)
        free(statString[i]);
    free(statString);
}
