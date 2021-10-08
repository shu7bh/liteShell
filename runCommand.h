#ifndef RUN_COMMAND_H
#define RUN_COMMAND_H

// Tokenizes and checks bg process before running the command
void preRunCommand(char*);

// Runs the command. Pipes have to be implemented before this function.
// This function handles input output redirection
void runCommand(char**, int, int);

#endif
