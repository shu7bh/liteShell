#include "../headers.h"
#include "echo.h"

void echo(char** argv, int argc)
{
    for (int i = 0; i < argc; ++i)
        printf("%s ", argv[i + 1]);
    printf("\n");
}
