#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../lib/libini/ini.h"
#include "configparser.h"

const char* CONFIG_PATH = "config.ini";

static int client_handler(void* user, const char* section, const char* name, const char* value) {
    configuration* pconfig = (configuration*) user;
    confClient* pclient = &pconfig->client;

    if (strcmp(section, "Client") == 0 && strcmp(name, "port") == 0) {
        pclient->port = atoi(value);
    } else {
        return 0; // Unknown name
    }

    return 1;
}

static int central_handler(void* user, const char* section, const char* name, const char* value) {
    configuration* pconfig = (configuration*) user;
    confClient* ppair = &pconfig->pair;
    confClient* pimpair = &pconfig->impair;

    if (strcmp(section, "Pair") == 0) {
        if (strcmp(name, "ip") == 0) {
            ppair->ip = strdup(value);
        } else if (strcmp(name, "port") == 0) {
            ppair->port = atoi(value);
        } else {
            return 0; // Unknown name
        }
    } else if (strcmp(section, "Impair") == 0) {
        if (strcmp(name, "ip") == 0) {
            pimpair->ip = strdup(value);
        } else if (strcmp(name, "port") == 0) {
            pimpair->port = atoi(value);
        } else {
            return 0; // Unknown name
        }
    } else {
        return 0; // Unknown section
    }

    return 1;
}

configuration load_config(ModuleType type) {
    confClient pair = {"0.0.0.0", 0};
    confClient impair = {"0.0.0.0", 0};
    confClient client = {"0.0.0.0", 0};

    error err = {ERROR_NONE, ""};

    configuration config = {
        pair,
        impair,
        client,
        type,
        err
    };

    configuration* pconfig = &config;
    error* perr = &pconfig->err;
    int error_ini_parse = -1;

    if (type == MODULE_CENTRAL) {
        error_ini_parse = ini_parse(CONFIG_PATH, central_handler, &config);
    } else {
        error_ini_parse = ini_parse(CONFIG_PATH, client_handler, &config);
    }

    if (error_ini_parse < 0) {
        if (error_ini_parse == -1) {
            perr->id = ERROR_FILE_NOT_READABLE;
            perr->message = "Le fichier de configuration n'a pas pu être ouvert.";
        } else {
            perr->id = ERROR_INI_PARSE_FAIL;
            perr->message = "Le fichier de configuration est invalide ou corrompu.";
        }
    }

    return config;
}

char* default_config_string(ModuleType type) {
    if (type == MODULE_CENTRAL) {
        return "[Pair]\nip=127.0.0.1\nport=766\n[Impair]\nip=127.0.0.1\nport=766\n";
    } else {
        return "[Client]\nport=766\n";
    }
}

error create_default_config(ModuleType type) {
    FILE *f;
    error err = {ERROR_NONE, ""};

    f = fopen(CONFIG_PATH, "w");

    if (!f) {
        err.id=ERROR_FILE_NOT_WRITABLE;
        err.message = "Impossible de créer le fichier de configuration";
    } else {
        if (fprintf(f, "%s", default_config_string(type)) < 0) {
            err.id = ERROR_FILE_WRITE_FAIL;
            err.message = "A unknown error has happened while writing the configuration file";
        }

        fclose(f);
    }

    return err;
}
