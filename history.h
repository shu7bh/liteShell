#ifndef HISTORY_H
#define HISTORY_H

void addCommand(char* command);
void printCommand(int argc, char** argv);
char* getNextHistory(int* prev);
char* getPrevHistory(int* prev);

#endif
