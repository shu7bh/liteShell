#include "inputOutputRedirection.h"
#include "../headers.h"
#include "fcntl.h"

int changeIO(int fd, int current);

/*int inputOutputRedirection(char** argv, int* argc)*/
/*{*/
/*int ct = 0;*/
/*int a = 0, b = 0, c = 0;*/

/*for (int i = 0; i <= *argc; ++i)*/
/*{*/
/*char *safePtr, copy[SIZE], str[SIZE];*/
/*strcpy(copy, argv[i]);*/
/*strcpy(str, argv[i]);*/

/*char* token = strtok_r(str, "<>", &safePtr);*/

/*if (!token)*/
/*switch (argv[i][0])*/
/*{*/
/*case '<':*/
/*a = 1;*/
/*break;*/
/*case '>':*/
/*if (b)*/
/*c = 1, b = 0;*/
/*else*/
/*b = 1;*/
/*break;*/
/*}*/

/*while (token)*/
/*{*/
/*switch (copy[token - str - 1])*/
/*{*/
/*case '<':*/
/*a = 1;*/
/*break;*/
/*case '>':*/
/*if (b)*/
/*c = 1, b = 0;*/
/*else*/
/*b = 1;*/
/*break;*/
/*}*/

/*if (a)*/
/*{*/
/*a = 0;*/
/*int fd = open(token, O_RDONLY, 0644);*/

/*if (!changeIO(fd, STDIN_FILENO))*/
/*return 0;*/
/*}*/
/*else if (b)*/
/*{*/
/*b = 0;*/
/*int fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);*/

/*if (!changeIO(fd, STDOUT_FILENO))*/
/*return 0;*/
/*}*/
/*else if (c)*/
/*{*/
/*c = 0;*/
/*int fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);*/

/*if (!changeIO(fd, STDOUT_FILENO))*/
/*return 0;*/
/*}*/
/*else*/
/*strcpy(argv[ct++], token);*/

/*token = strtok_r(NULL, "<>", &safePtr);*/
/*}*/
/*}*/

/*--ct;*/

/*for (int i = ct + 1; i <= *argc; ++i)*/
/*{*/
/*free(argv[i]);*/
/*argv[i] = 0;*/
/*}*/

/**argc = ct;*/

/*if (a || b || c)*/
/*return 0;*/

/*return 1;*/
/*}*/

int inputOutputRedirection(char** argv, int* argc)
{
    int ct = 0;

    for (int i = 0; i <= *argc; ++i)
    {
        char* str = argv[i];

        if (!strcmp(str, "<"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_RDONLY, 0644);

                if (!changeIO(fd, STDIN_FILENO))
                    return 0;
            }
            else
                return 0;
        else if (!strcmp(str, ">"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (!changeIO(fd, STDOUT_FILENO))
                    return 0;
            }
            else
                return 0;
        else if (!strcmp(str, ">>"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

                if (!changeIO(fd, STDOUT_FILENO))
                    return 0;
            }
            else
                return 0;
        else
            strcpy(argv[ct++], str);
    }
    --ct;

    for (int i = ct + 1; i <= *argc; ++i)
    {
        free(argv[i]);
        argv[i] = 0;
    }
    *argc = ct;
    return 1;
}

int changeIO(int fd, int current)
{
    if (fd < 0)
    {
        perror("open error");
        return 0;
    }

    if (dup2(fd, current) < 0)
    {
        perror("Unable to duplicate file descriptor.");
        return 0;
    }

    close(fd);
    return 1;
}

// code <abc.txt>hello.txt
// code >abc.txt<hello.txt
// code > abc.txt < hello.txt
// code > abc.txt<hello.txt
// code <hello.txt>abc.txt
