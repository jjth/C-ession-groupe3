#ifndef GLOBALS_H
#define GLOBALS_H
#define TRUE 1
#define FALSE 0

typedef enum ModuleType ModuleType;

enum ModuleType {
    MODULE_CENTRAL,
    MODULE_PAIR,
    MODULE_IMPAIR
};

typedef enum ErrorType ErrorType;

enum ErrorType {
    ERROR_NONE,
    ERROR_FILE_NOT_READABLE,
    ERROR_FILE_NOT_WRITABLE,
    ERROR_FILE_WRITE_FAIL,
    ERROR_INI_PARSE_FAIL,
    ERROR_MEMORY_ALLOCATION
};

typedef struct {
    ErrorType id;
    char* message;
} error;
#endif
