#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFile.h"
#define MAX_LINE 2048

file_read openFile(char* fileName) {
    error err = {
        ERROR_NONE,
        ""
    };

    file_read file = {
        0,
        NULL,
        0,
        0,
        err
    };
    printf("1\n");
    error* perr = &err;
        printf("2\n");
    char* line = malloc(MAX_LINE*sizeof(char*));
        printf("3\n");
    int lineSize = MAX_LINE;
    int nbColumns = -1;
        printf("4\n");
    file_read* pfile = &file;
    printf("5\n");
    if (!line) {
            printf("6\n");
        perr->id = ERROR_MEMORY_ALLOCATION;
        perr->message = "Memory allocation failed";
    } else {
            printf("7\n");
        FILE* file_pointer = fopen(fileName, "r");
    printf("8\n");

        if (!file_pointer) {
            perr->id = ERROR_FILE_NOT_READABLE;
            perr->message = "The file couldn't be accessed, please check your path.";
        } else {
            fgets(line, lineSize, file_pointer);
            
            while (line[strlen(line) - 1] != '\n' || line[strlen(line) - 1] != '\r') {
                char* tmp = realloc(line, lineSize + MAX_LINE);

                if (!tmp) {
                    perr->id = ERROR_MEMORY_ALLOCATION;
                    perr->message = "Memory allocation failed";

                    return file;
                } else {
                    line = tmp;
                    lineSize += MAX_LINE;
                    fseek(file_pointer,0,SEEK_SET);
                    fgets(line, lineSize, file_pointer);
                }
            }

            fseek(file_pointer,0,SEEK_SET);
            nbColumns = strlen(line);

            pfile->column_count = nbColumns;
            pfile->file = file_pointer;
            pfile->init_done = TRUE;
            }
    }

    return file;
}

char* readLine(file_read file) {
    if (file.column_count > 0 && file.err.id == ERROR_NONE && file.init_done == TRUE) {
        if (!file.file) {
            return NULL;
        } else {
            char* line = malloc(sizeof(char*)*(file.column_count+1));

            if (!line) {
                return NULL;
            } else {
                if (fgets(line, file.column_count, file.file)) {
                    return line;
                } else {
                    return "";
                }
            }
        }
    } else {
        return NULL;
    }
}
