#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

#if defined(WIN32) || defined(_WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
char *strsep(char **stringp, const char *delim) {
  if (*stringp == NULL) { return NULL; }
  char *token_start = *stringp;
  *stringp = strpbrk(token_start, delim);
  if (*stringp) {
    **stringp = '\0';
    (*stringp)++;
  }
  return token_start;
}
#endif

CommandType get_command(char* string) {
    if (strlen(string) < 10) {
        return CMD_UNKNOWN;
    } else {
        char cmdbuffer[10];
        memcpy(cmdbuffer, &string[0], 10);
        cmdbuffer[10] = '\0';

        if (strcmp(cmdbuffer, __CMD_SEND_LINE) == 0) {
            return CMD_SEND_LINE;
        } else if (strcmp(cmdbuffer, __CMD_RESET) == 0) {
            return CMD_RESET;
        } else if (strcmp(cmdbuffer, __CMD_GET_CHAR) == 0) {
            return CMD_GET_CHAR;
        } else if (strcmp(cmdbuffer, __CMD_SET_CHAR) == 0) {
            return CMD_SET_CHAR;
        } else if (strcmp(cmdbuffer, __CMD_GET_COLOR) == 0) {
            return CMD_GET_COLOR;
        } else if (strcmp(cmdbuffer, __CMD_SET_COLOR) == 0) {
            return CMD_SET_COLOR;
        } else if (strcmp(cmdbuffer, __CMD_TIME_NEW) == 0) {
            return CMD_TIME_NEW;
        } else {
            return CMD_UNKNOWN;
        }
    }
}

char* get_recv_data(char* string) {
    if (strlen(string) < 10) {
        return "";
    }

    long new_str_size = strlen(string) - 10;
    char* data;
    data = malloc(sizeof(char*) * (new_str_size+1));
    memcpy(data, &string[10], new_str_size);
    data[new_str_size] = '\0';

    return data;
}

char** str_split(char* string) {
    char* token;
    char* str = strdup(string);
    char* toFree;
    char** result;
    int i;

    toFree = str = strdup(string);
    // Count the number of ";"
    for (i = 0; str[i]; str[i] == ';' ? i++ : *str++);
    free(toFree);

    result = malloc(sizeof(char*)*(i+1));

    toFree = str = strdup(string);
    i = 0;
    while((token = strsep(&str, ";"))) {
        result[i] = token;
        i++;
    }

    free(str);

    return result;
}
