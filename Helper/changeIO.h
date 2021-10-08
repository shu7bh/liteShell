#ifndef CHANGEIO_H
#define CHANGEIO_H

// Redirects using dup2 from old fd to new fd
int changeIO(int, int);

#endif
