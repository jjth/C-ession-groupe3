#include <string.h>
#include "globals.h"

CommandType get_command(char* string) {
    if (strlen(string) < 10) {
        return CMD_UNKNOWN;
    } else {
        char cmdbuffer[10];
        memcpy(cmdbuffer, &string[0], 10);
        cmdbuffer[10] = '\0';

        if (strcmp(string, __CMD_SEND_LINE) == 0) {
            return CMD_SEND_LINE;
        } else if (strcmp(string, __CMD_RESET) == 0) {
            return CMD_RESET;
        } else if (strcmp(string, __CMD_GET_CHAR) == 0) {
            return CMD_GET_CHAR;
        } else if (strcmp(string, __CMD_SET_CHAR) == 0) {
            return CMD_SET_CHAR;
        } else if (strcmp(string, __CMD_GET_COLOR) == 0) {
            return CMD_GET_COLOR;
        } else if (strcmp(string, __CMD_SET_COLOR) == 0) {
            return CMD_SET_COLOR;
        } else if (strcmp(string, __CMD_TIME_NEW) == 0) {
            return CMD_TIME_NEW;
        } else {
            return CMD_UNKNOWN;
        }
    }
}
