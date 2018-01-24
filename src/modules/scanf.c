#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../globals.h"
#include "scanf.h"

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#define Sleep(x) usleep((x)*1000)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif

char* scanfLineWithMax(int maxLength) {
    char* scannedLine = malloc(sizeof(char*)*maxLength);

    char c;
    scannedLine[0] = '\0';
    int i = 0;
    int cursorPos = i;
    // While the user didn't press "ENTER".
    do {
        int skipChar = FALSE;
        c = getch();
        if (c == 127) {
            if (cursorPos > 0) {
                int o = 0;
                int u = 0;
                int addedChars = 0;
                printf("\b");
                while (o < i && scannedLine[o] != '\0' && o < maxLength) {
                    scannedLine[u] = scannedLine[o];

                    if (o != (cursorPos -1)) {
                        if (u < o) {
                            printf("%c", scannedLine[u]);
                            addedChars += 1;
                        }
                        u=u+1;
                    }

                    o=o+1;
                }

                printf("%c\b ", scannedLine[u]);

                for (o = addedChars; o >= 0; o--) {
                    printf("\b");
                }                        
                i -= 1;
                cursorPos -= 1;
                scannedLine[i] = '\0';
            }
            skipChar = TRUE;
        } else if (c == 27) {
            c = getch();
            if (c == 91) {
                c = getch();
                if (c > 64 && c < 69) {
                    if (c == 67 && cursorPos < i) {
                        cursorPos += 1;
                        printf("\033[1C");
                    } else if (c == 68 &&cursorPos > 0 ) {
                        cursorPos -= 1;
                        printf("\033[1D");
                    }

                    skipChar = TRUE;
                }
            }
        }

        if (i < maxLength && skipChar == FALSE && c != '\n') {
            putchar(c);

            int u = 0;
            int o = 0;
            
            if (cursorPos == i) {
                scannedLine[i] = c;
            } else {
                char* scannedLineCopy = malloc(sizeof(char*)*maxLength);
                strcpy(scannedLineCopy, scannedLine);

                u = 0;
                o = 0;
                
                while(o <= i) {
                    scannedLineCopy[u] = scannedLine[o];

                    if (o == cursorPos) {
                        scannedLineCopy[u+1] = scannedLine[o];

                        scannedLineCopy[u] = c;

                        u++;
                    }

                    if (u > o) {
                        putchar(scannedLineCopy[u]);
                    }

                    u++;
                    o++;
                }

                for (o = o; o > cursorPos; o--) {
                    printf("\b");
                }
                free(scannedLine);
                scannedLine = scannedLineCopy;
            }


            cursorPos += 1;
            i=i+1;
        }

    //printf("FILE: %s\n", scannedLine);
    } while(c != EOF && c != '\n');
    printf("\n");

    return scannedLine;
}

char* scanfLine() {
    return scanfLineWithMax(256);
}

char scanfChar() {
    char* c = scanfLineWithMax(1);

    return c[0];
}

int scanfInt() {
    char* startPtr = scanfLine();
    char* endPtr;

    long result = strtol(startPtr, &endPtr, 10);
    
    if (strcmp(endPtr, "\0") == 0) {
        // String parsed successfully
        if (result <= INT_MAX) {
            return (int) result;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void emptyBuffer() {
    getchar();
}
