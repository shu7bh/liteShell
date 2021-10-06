#include "commandAutoCompletion.h"
#include "../headers.h"
#include "../Helper/token.h"
#include "../Helper/homeDir.h"
#include "makeChild.h"
#include <dirent.h>

int nextArgument(char* command, int* ct, int addOrSub, char* ogCommand);
char * strrstr(char*s1, char* s2);

char ogCommand[SIZE];
int isCommand = 1;

int autoComplete(char* command, int* ct, int addOrSub)
{
    if (!strlen(command))
        return 0;

    switch (command[strlen(command) - 1])
    {
        case ' ':
        case '\t':
            return 0;
        default:
            break;
    }

    char prefix[SIZE];
    strcpy(prefix, command);

    char inp[SIZE];
    strcpy(inp, command);

    char** argv = malloc(SIZE);
    int argc, temp;

    if (!tokenize(inp, argv, &argc, &temp))
        return 0;

    char curCommand[SIZE];
    strcpy(curCommand, argv[argc]);

    for (int i = 0; i <= argc; ++i)
        free(argv[i]);

    free(argv);

    char* p = strrstr(prefix, curCommand);

    if (p)
        memset(p, 0, strlen(p));

    if (!*ct)
    {
        strcpy(ogCommand, curCommand);
        char dir[SIZE];

        if (argc)
        {
            char* a = strrchr(curCommand, '/');
            if (a)
                if (!strcmp(a, curCommand))
                    strcpy(dir, "/");
                else
                {
                    a[0] = 0;
                    strcpy(dir, curCommand);
                }
            else
                strcpy(dir, ".");
            isCommand = 0;
        }
        else
            strcpy(dir, "/usr/bin"), isCommand = 1;

        struct dirent *directory;
        DIR *d = opendir(dir);

        if (!d)
            return 0;

        char path[SIZE];
        sprintf(path, "%s/%s", getHomeDir(), ".liteShell/args.txt");

        FILE* fp = fopen(path, "w");

        if (!fp)
        {
            logError("fopen error");
            return 0;
        }

        fprintf(fp, "%s\n", ogCommand);

        while ((directory = readdir(d)))
        {
            fprintf(fp, "%s", directory->d_name);

            char path[SIZE];
            sprintf(path, "%s/%s", dir, directory->d_name);
            DIR* checkDir = opendir(path);
            if (checkDir)
            {
                fprintf(fp, "/");
                free(checkDir);
            }

            fprintf(fp, "\n");
        }

        fclose(fp);

        char* commandArg[2];
        sprintf(path, "%s/%s", getHomeDir(), ".liteShell/trie");
        commandArg[0] = strdup(path);
        commandArg[1] = 0;

        closedir(d);
        makeChildFg(commandArg);
        free(commandArg[0]);
    }

    memset(inp, 0, SIZE);
    if (!nextArgument(inp, ct, addOrSub, ogCommand))
        return 0;

    sprintf(command, "%s%s", prefix, inp);

    return 1;
}

int nextArgument(char* command, int* ct, int addOrSub, char* ogCommand)
{
    char path[SIZE];
    sprintf(path, "%s/%s", getHomeDir(), ".liteShell/return.txt");

    FILE* fin = fopen(path, "r");
    if (!fin)
    {
        logError("fopen error");
        return 0;
    }

    char string[SIZE];
    int linect;

    for (linect = 0; !feof(fin); ++linect)
        fgets(string, SIZE, fin);

    fseek(fin, 0, SEEK_SET);
    *ct = (linect + *ct + addOrSub) % linect;

    switch (linect)
    {
    case 1: return 0;
    case 2:
        fscanf(fin, "%s", string);

        if (isCommand)
            sprintf(command, "%s ", string);
        else
            sprintf(command, "%s", string);
        return 1;

    default: break;
    }

    int i = 0;
    for (; i < *ct; ++i)
        fgets(string, SIZE, fin);

    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = 0;

    if (i)
        strcpy(command, string);
    else
        strcpy(command, ogCommand);

    fclose(fin);
    return 1;
}

char* strrstr(char* s1, char* s2)
{
    char* ss1;
    char* sss1;
    char* sss2;

    if(*(s2) == '\0')
        return s1;

    ss1 = s1 + strlen(s1);

    while(ss1 != s1)
    {
        --ss1;

        for(sss1 = ss1, sss2 = s2;;)
            if(*(sss1++) != *(sss2++))
                break;
            else if (*sss2 == '\0')
                return ss1;
    }

    return NULL;
}
