#ifndef HEADERS_H
#define HEADERS_H

#include "Helper/logError.h"
#include "Helper/colors.h"
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 4096

typedef struct Fg
{
    int pid;
    char name[SIZE];
    char command[SIZE];
} Fg;

extern Fg fgDetails;
extern int color;
void clearFg();
void addFgAr(int pid, char** command);
void addFg(int pid, char* name, char* command);

#endif
