#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <malloc.h>

#define SIZE 4096

typedef struct Fg
{
    int pid;
    char command[SIZE];
    char args[SIZE];
} Fg;

extern Fg fg;

#endif
