#ifndef SCANF_H
#define SCANF_H
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
/* reads from keypress, doesn't echo */
int getch(void);
#endif

char* scanfLine();
#endif
