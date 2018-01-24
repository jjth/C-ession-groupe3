#ifndef GLOBALS_H
#define GLOBALS_H
#define TRUE 1
#define FALSE 0

#define __CMD_SEND_LINE   "[%%]LINE  "
#define __CMD_RESET       "[%%]RESET "
#define __CMD_GET_CHAR    "[%%]GETCAR"
#define __CMD_SET_CHAR    "[%%]SETCAR"
#define __CMD_GET_COLOR   "[%%]GETCOL"
#define __CMD_SET_COLOR   "[%%]SETCOL"
#define __CMD_TIME_NEW    "[%%]NEWT0 "

typedef enum CommandType CommandType;

enum CommandType {
    CMD_SEND_LINE,
    CMD_RESET,
    CMD_GET_CHAR,
    CMD_SET_CHAR,
    CMD_GET_COLOR,
    CMD_SET_COLOR,
    CMD_TIME_NEW,
    CMD_UNKNOWN
};

typedef enum ModuleType ModuleType;

enum ModuleType {
    MODULE_CENTRAL,
    MODULE_PAIR,
    MODULE_IMPAIR
};

typedef enum ErrorType ErrorType;

enum ErrorType {
    ERROR_NONE, //0
    ERROR_OPERATION_NOT_PERMITTED, //1
    ERROR_FILE_NOT_FOUND, //2
    ERROR_FILE_NOT_READABLE, //3
    ERROR_FILE_NOT_WRITABLE,
    ERROR_FILE_WRITE_FAIL,
    ERROR_INI_PARSE_FAIL,
    ERROR_HOST_UNKNOWN,
    ERROR_HOST_DOWN,
    ERROR_MEMORY_ALLOCATION
};

typedef struct {
    ErrorType id;
    char* message;
} error;
#endif
