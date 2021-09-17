#include "input.h"
#include "headers.h"
#include <stddef.h>

char* inputBuffer;
size_t inputBufferSize;

void setInputVar()
{
    inputBufferSize = 1000;
    inputBuffer = malloc(inputBufferSize);
}

char* input()
{

    getline(&inputBuffer, &inputBufferSize, stdin);
    inputBuffer[strlen(inputBuffer) - 1] = 0; // Remove newline

    return inputBuffer;
}
