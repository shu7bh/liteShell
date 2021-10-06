#include "inputOutputRedirection.h"
#include "changeIO.h"
#include "../headers.h"
#include <fcntl.h>

int changeIO(int fd, int current);

int inputOutputRedirection(char** argv, int* argc)
{
    int ct = 0;

    for (int i = 0; i <= *argc; ++i)
    {
        char* str = argv[i];

        if (!strcmp(str, "<"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_RDONLY);

                if (!changeIO(fd, STDIN_FILENO))
                    return 0;
            }
            else
            {
                logStdError("File not provided");
                return 0;
            }
        else if (!strcmp(str, ">"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

                if (!changeIO(fd, STDOUT_FILENO))
                    return 0;
            }
            else
            {
                logStdError("File not provided");
                return 0;
            }
        else if (!strcmp(str, ">>"))
            if (i + 1 <= *argc)
            {
                int fd = open(argv[i++ + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

                if (!changeIO(fd, STDOUT_FILENO))
                    return 0;
            }
            else
            {
                logStdError("File not provided");
                return 0;
            }
        else
            strcpy(argv[ct++], str);
    }

    for (int i = ct--; i <= *argc; ++i)
    {
        free(argv[i]);
        argv[i] = 0;
    }

    *argc = ct;
    return 1;
}
