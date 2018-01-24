#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

    error* perr = &err;

    char* line = malloc(MAX_LINE*sizeof(char*));

    int nbColumns = -1;

    file_read* pfile = &file;

    if (!line) {
        perr->id = ERROR_MEMORY_ALLOCATION;
        perr->message = "Memory allocation failed";
    } else {
        FILE* file_pointer = fopen(fileName, "r");

        if (!file_pointer) {
            if (errno == ERROR_FILE_NOT_FOUND) {
                perr->id = ERROR_FILE_NOT_FOUND;
                perr->message = "Fichier introuvable, veuillez réessayer.";
            } else {
                perr->id = ERROR_FILE_NOT_READABLE;
                perr->message = "Fichier inaccessible, veuillez réessayer.";
            }
        } else {
            char c;

            nbColumns = 0;

            c = fgetc(file_pointer);

            while (c != EOF && c != '\n') {
                ++nbColumns;
                c = fgetc(file_pointer);
            }

            fseek(file_pointer,0,SEEK_SET);

            pfile->column_count = nbColumns;
            pfile->file = file_pointer;
            pfile->init_done = TRUE;
            }

        pfile->err = *perr;
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
                if (fgets(line, file.column_count+2, file.file)) {
                    if (line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r' || line[strlen(line) - 1] == EOF) {
                        // Strip-off unwanted characters
                        char *p = strchr(line, '\n');
                        if (p) *p = 0;
                        p = strchr(line, '\r');
                        if (p) *p = 0;
                        p = strchr(line, EOF);
                        if (p) *p = 0;
                        return line;
                    } else {
                        return "";
                    }
                } else {
                    return "";
                }
            }
        }
    } else {
        return NULL;
    }
}
