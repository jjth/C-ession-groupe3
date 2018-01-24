#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

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
