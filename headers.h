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
extern int commandTime;

// Clears input for the global variable fgDetails
void clearFg();

// Sets fgDetails
void addFgAr(int pid, char** command);

// Sets fgDetails
void addFg(int pid, char* name, char* command);

#endif
