#include "echo.h"
#include "headers.h"

void echo(char** argv)
{
    for (int i = 0; strcmp(argv[i], ""); ++i)
        printf("%s ", argv[i]);
    printf("\n");
}
