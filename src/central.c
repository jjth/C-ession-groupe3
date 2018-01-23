#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "globals.h"
#include "modules/configparser.h"
#include "modules/colors.h"
#include "modules/readLines.h"
#include "modules/rulesParser.h"

#define LINE_SIZE 5
#define NB_LINE 5

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

typedef int SOCKET;

typedef struct {
    int connected;
    error err;
    SOCKET socket;
} NetworkClientConnection;

NetworkClientConnection connect_client(const char* ip, int port) {
    error err = {
        ERROR_NONE,
        ""
    };

    NetworkClientConnection conn = {
        TRUE,
        err,
        0
    };

    return conn;
}
/**
 * Output an error to the user.
 */
void print_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    setColor(1); // 1 = RED (see ANSI color codes)
    printf(format, args);
    resetColor();

    va_end(args);
}

int main(int argc, char const *argv[])
{
    //////////////////////////
    ///////// Load the 
    ///////// configuration file
    //////////////////////////

    int conf_fatal_error = TRUE;
    configuration conf = load_config(MODULE_CENTRAL);

    // Try to load configuration and handle all use-cases
    if (conf.err.id == ERROR_NONE) {
        conf_fatal_error = FALSE; // Loading succeed
    } else if (conf.err.id == ERROR_FILE_NOT_READABLE) {
        printf("No configuration file found.");
        // File not readable = potentially "file not found" so
        // we'll try to create it.
        error default_config_creation = create_default_config(MODULE_CENTRAL);

        if (default_config_creation.id == ERROR_NONE) { // config.ini file created successfully
            printf(" Using default configuration.\n");

            // Reload the configuration we've just created.
            conf = load_config(MODULE_CENTRAL);

            if (conf.err.id == ERROR_NONE) {
                conf_fatal_error = FALSE;
            } else {
                print_error("Couldn't load the default configuration: %s", conf.err.message);
            }
        } else { // Cannot create a file in this folder => insufficient rights.
            print_error("\nCouldn't create a configuration file, please ask an administrator to verify");
            print_error(" that you have sufficient rights in this folder.\n");
        }
    } else {
        print_error("Couldn't load the configuration: %s", conf.err.message);
    }

    if (conf_fatal_error == FALSE) {
        if (strcmp(conf.pair.ip, "0.0.0.0") == 0 ||
            conf.pair.port == 0 ||
            strcmp(conf.impair.ip, "0.0.0.0") == 0 ||
            conf.impair.port == 0) {
            conf_fatal_error = TRUE;
            print_error("Configuration is invalid, please contact your administrator.\n");
        }
    }

    if (conf_fatal_error == TRUE) {
        return -1;
    }

    //////////////////////////
    ///////// Connection to the "pair"
    /////////  & "impair" modules.
    //////////////////////////

    // TODO: stocker nbLignes & nbColonnes
    int pairConnectionOK = FALSE;
    int impairConnectionOK = FALSE;

    NetworkClientConnection conn_pair = connect_client(conf.pair.ip, conf.pair.port);
    NetworkClientConnection conn_impair = connect_client(conf.pair.ip, conf.pair.port);
    
    pairConnectionOK = conn_pair.connected;
    impairConnectionOK = conn_impair.connected;

    if (pairConnectionOK == TRUE && impairConnectionOK == TRUE) {
        printf("Module central connecté aux modules pair & impair.\n");
    } else {
        if (pairConnectionOK == TRUE) {
            printf("Module central connecté au module pair.\n");
        } else if (impairConnectionOK == TRUE) {
            printf("Module central connecté au module impair.\n");
        }

        printf("En attente de connection...");
        while(pairConnectionOK == FALSE || impairConnectionOK == FALSE) {
            printf(".");
            fflush(stdout);
            // Wait 0.5 seconds...
            Sleep(500);

            if (pairConnectionOK == FALSE) {
                conn_pair = connect_client(conf.pair.ip, conf.pair.port);
            
                if (conn_pair.connected == TRUE) {
                    printf("\nModule central connecté au module pair.\n");
                    pairConnectionOK = TRUE;
                }
            }

            if (impairConnectionOK == FALSE) {
                conn_impair = connect_client(conf.impair.ip, conf.impair.port);
            
                if (conn_impair.connected == TRUE) {
                    printf("\nModule central connecté au module impair.\n");
                    impairConnectionOK = TRUE;
                }
            }
        }

        printf("Connection OK\n");
    }

    //////////////////////////
    ///////// POLL USER
    ///////// 
    //////////////////////////

    // TODO: SCANF: LIGNE PAR LIGNE:
    // 
    int* matrixSize;
    matrixSize = ask_lines();
    // OU CHEMIN DU FICHIER A CHARGER

    printf("Taille de la matrice: [%dx%d]\n", matrixSize[0], matrixSize[1]);
    // TODO:
    // Demander les rules (rulesParser)
    ask_rules();

    // Algo final de remplacement
    // & display de Chaka
	return 0;
}