#include <stdio.h>
#include <stdarg.h>
#include "./modules/dataStructure.h"
#include "./modules/colors.h"
#include "./modules/configparser.h"
#include "./modules/server.h"

void print_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    setColor(1); // 1 = RED (see ANSI color codes)
    printf(format, args);
    resetColor();

    va_end(args);
}

int main(int argc, char **argv){
	int conf_fatal_error = TRUE;
    configuration conf = load_config(MODULE_PAIR);

    // Try to load configuration and handle all use-cases
    if (conf.err.id == ERROR_NONE) {
        conf_fatal_error = FALSE; // Loading succeed
    } else if (conf.err.id == ERROR_FILE_NOT_FOUND) {
        printf("Fichier de configuration introuvable.");
        // File not found: create default configuration.
        error default_config_creation = create_default_config(MODULE_PAIR);

        if (default_config_creation.id == ERROR_NONE) { // config.ini file created successfully
            printf(" Utilisation de la configuration par défaut.\n");

            // Reload the configuration we've just created.
            conf = load_config(MODULE_PAIR);

            if (conf.err.id == ERROR_NONE) {
                conf_fatal_error = FALSE;
            } else {
                print_error("Impossible de charger la configuration par défaut: %s", conf.err.message);
            }
        } else { // Cannot create a file in this folder => insufficient rights.
            print_error("\nImpossible de créer le fichier de configuration, veuillez demander à un administrateur");
            print_error(" de vérifier que vous avez des droits suffisants sur ce dossier.\n");
        }
    } else {
        print_error("Impossible de charger la configuration: %s", conf.err.message);
    }

    if (conf_fatal_error == FALSE) {
        if (conf.client.port == 0) {
            conf_fatal_error = TRUE;
            print_error("La configuration est invalide, veuillez contacter un administrateur.\n");
        }
    }

    if (conf_fatal_error == TRUE) {
        return -1;
    }
	init();
	
	app(conf.client.port, MODULE_PAIR);

	end();

	return 0;
}
