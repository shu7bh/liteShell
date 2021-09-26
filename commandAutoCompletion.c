#include "commandAutoCompletion.h"
#include "headers.h"
#include "token.h"
#include "makeChild.h"
#include <dirent.h>

void autoComplete(char* command)
{
    char* inp = strdup(command);
    if (!strlen(inp))
        return;

    if (inp[strlen(inp) - 1] == ' ')
        return;

    char** argv = malloc(SIZE);
    int argc, temp;

    if (tokenize(inp, argv, &argc, &temp))
        if (argc)
            return;

    char* dir = "/usr/bin";
    struct dirent *directory;
    DIR *d = opendir(dir);

    if (!d)
    {
        perror("open dir error");
        return;
    }

    FILE* fp = fopen(".liteShell/args.txt", "w");

    fprintf(fp, "%s\n", inp);
    while ((directory = readdir(d)))
        fprintf(fp, "%s\n", directory->d_name);

    fclose(fp);

    char* commandArg[2];
    commandArg[0] = strdup("./.liteShell/trie");
    commandArg[1] = 0;

    makeChildFg(commandArg);

    fp = fopen("./.liteShell/return.txt", "r");

    if (!fp)
    {
        perror("file error");
        return;
    }

    int hmm;
    fscanf(fp, "%d", &hmm);
    printf("%d\n", hmm);

    pclose(fp);
}
