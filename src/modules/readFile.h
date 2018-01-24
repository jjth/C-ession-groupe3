#ifndef READFILE_H
#define READFILE_H
#include <stdio.h>
#include "../globals.h"

typedef struct {
    int init_done;
    FILE* file;
    int current_line;
    int column_count;
    error err;
} file_read;

file_read openFile(char* fileName);
char* readLine(file_read file);
#endif
