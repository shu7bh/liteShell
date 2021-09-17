#include "stringToNum.h"
#include "headers.h"

int stringToNum(char* str)
{
    int num = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        num *= 10;
        int ascii = str[i] - '0';
        if (ascii > 9 || ascii < 0)
        {
            printf("Error: Number is not provided\n");
            return -1;
        }
        num += ascii;
    }
    return num;
}
