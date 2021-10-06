#include "colors.h"
#include "../headers.h"

int color = 1;

void green()
{
    if (color)
        printf("\033[0;92m");
}
void blue()
{
    if (color)
        printf("\033[0;94m");
}
void red()
{
    if (color)
        printf("\033[0;91m");
}
void yellow()
{
    if (color)
        printf("\033[0;93m");
}
void magenta()
{
    if (color)
        printf("\033[0;95m");
}
void reset()
{
    if (color)
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
