#ifndef HISTORY_H
#define HISTORY_H

#include "../headers.h"

void addCommand(char*);
void printCommand(char**, int);

char* getNextHistory(int*);
char* getPrevHistory(int*);

void loadHistory();

extern char his[10002][SIZE];
extern int end;

#endif
