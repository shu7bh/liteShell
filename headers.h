#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <malloc.h>
#include "Helper/colors.h"

#define SIZE 4096

typedef struct Fg
{
    int pid;
    char name[SIZE];
    char command[SIZE];
} Fg;

extern Fg fgDetails;

#endif
