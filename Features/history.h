#ifndef HISTORY_H
#define HISTORY_H

#include "../headers.h"

void addCommand(char* command);
void printCommand(int argc, char** argv);
char* getNextHistory(int* prev);
char* getPrevHistory(int* prev);
void loadHistory();

extern char his[10002][SIZE];
extern int end;

#endif
