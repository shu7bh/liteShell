#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <malloc.h>
#include "Helper/colors.h"
#include "Helper/logError.h"

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
