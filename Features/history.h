#ifndef HISTORY_H
#define HISTORY_H

#include "../headers.h"

// Adding command to history
void addCommand(char*);

// Printing latest commands
void printCommand(char**, int);

// Gets the next history
char* getNextHistory(int*);

// Gets the previous history
char* getPrevHistory(int*);

// Loads history into the 2D his array
void loadHistory();

extern char his[10002][SIZE];
extern int end;

#endif
