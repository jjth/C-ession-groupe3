#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#include "../globals.h"
typedef struct {
    const char* ip;
    int port;
} confClient;

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
