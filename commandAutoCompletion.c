#include "commandAutoCompletion.h"
#include "headers.h"
#include "token.h"
#include "makeChild.h"
#include <dirent.h>

char ogCommand[SIZE];

int autoComplete(char* command, int* ct, int addOrSub)
{
    if (!*ct)
    {
        char inp[SIZE];
        strcpy(inp, command);

        if (!strlen(inp))
            return 0;

        if (inp[strlen(inp) - 1] == ' ')
            return 0;

        char** argv = malloc(SIZE);
        int argc, temp;

        if (tokenize(inp, argv, &argc, &temp))
            if (argc)
                return 0;

        char* dir = "/usr/bin";
        struct dirent *directory;
        DIR *d = opendir(dir);

        if (!d)
        {
            perror("open dir error");
            return 0;
        }

        FILE* fp = fopen(".liteShell/args.txt", "w");

        fprintf(fp, "%s\n", inp);
        strcpy(ogCommand, inp);

        while ((directory = readdir(d)))
            fprintf(fp, "%s\n", directory->d_name);

        fclose(fp);

        char* commandArg[2];
        commandArg[0] = strdup("./.liteShell/trie");
        commandArg[1] = 0;

        makeChildFg(commandArg);
        free(commandArg[0]);
    }

    FILE* fin = fopen(".liteShell/return.txt", "r");
    if (!fin)
    {
        perror("fin error");
        return 0;
    }

    int r;

    fscanf(fin, "%d", &r);

    if (!r)
        return 0;

    char string[SIZE];
    int linect;

    for (linect = 0; !feof(fin); ++linect)
        fscanf(fin, "%s", string);

    fseek(fin, 0, SEEK_SET);
    fscanf(fin, "%s", string);

    if (r == -1)
    {
        fscanf(fin, "%s", string);
        sprintf(command, "%s ", string);
        return 1;
    }

    *ct = (linect + *ct + addOrSub) % linect;

    int i = 0;
    for (i = 0; i < *ct; ++i)
        fscanf(fin, "%s", string);

    if (i)
        strcpy(command, string);
    else
        strcpy(command, ogCommand);

    fclose(fin);
    return 1;
}
