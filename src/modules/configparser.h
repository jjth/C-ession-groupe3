#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

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
    const char* ip;
    int port;
} confClient;

typedef struct {
    ErrorType id;
    char* message;
} error;

typedef struct {
    confClient pair;
    confClient impair;
    confClient client;
    int type;
    error err;
} configuration;

extern configuration load_config(ModuleType type);
extern error create_default_config(ModuleType type);
char* default_config_string(ModuleType type);
#endif
