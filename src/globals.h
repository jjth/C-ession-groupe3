#ifndef GLOBALS_H
#define GLOBALS_H
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
    ERROR_INI_PARSE_FAIL
};

typedef struct {
    ErrorType id;
    char* message;
} error;
#endif
