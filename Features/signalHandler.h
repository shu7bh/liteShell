#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

// Handles ^c. Ends the foreground process
void ctrlc(int);

// Handles ^z. Puts the foreground process to the background
void ctrlz(int);

#endif
