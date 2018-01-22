#include "../src/globals.h"
#include "../src/modules/configparser.h"
#include <stdio.h>
#include <string.h>

int test_config()
{
    configuration conf = load_config(MODULE_CENTRAL);

    if (conf.err.id == ERROR_NONE) {
        fprintf(stderr, "The configuration file already exists!\n");
    } else if (conf.err.id == ERROR_FILE_NOT_READABLE) {
        error test = create_default_config(MODULE_CENTRAL);

        if (test.id == ERROR_NONE) {
            conf = load_config(MODULE_CENTRAL);

            if (conf.err.id == ERROR_NONE) {
                if (strcmp(conf.pair.ip, "127.0.0.1") == 0 && conf.pair.port == 766) {
                    return 0;
                } else {
                    fprintf(stderr, "Invalid values [IP: %s] [Port: %d].\n", conf.pair.ip, conf.pair.port);
                }
            } else {
                fprintf(stderr, "Error while creating the config file: %s.\n", test.message);
            }
        } else {
            fprintf(stderr, "Error while creating the config file: %s.\n", test.message);
        }
    }

    return -1;
}
