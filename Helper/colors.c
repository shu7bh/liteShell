#include "colors.h"
#include <stdio.h>

void green()
{
    printf("\033[0;92m");
}
void blue()
{
    printf("\033[0;94m");
}
void red()
{
    printf("\033[0;91m");
}
void yellow()
{
    printf("\033[0;93m");
}
void magenta()
{
    printf("\033[0;95m");
}
void reset()
{
    printf("\033[0;97m");
}
void cPrompt()
{
    printf("\033[1;96m");
}

void errorRed()
{
    fprintf(stderr, "\033[1;91m");
}

void errorReset()
{
    fprintf(stderr, "\033[0;97m");
}
