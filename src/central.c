#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "globals.h"
#include "modules/configparser.h"
#include "modules/colors.h"
#include "modules/readLines.h"
#include "modules/rulesParser.h"
#include "modules/readFile.h"
#include "modules/scanf.h"

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
/*
void send_to_network(char* line, int id){
	// TODO : VINCENT SEND DATA TO CLIENT 
	if((id%2)==0){
		//send to pair 
		printf("Send line to pair client\n");
	}else{
		//send to impair 
		printf("Send line to impair client\n");
	}
}
*/
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
    } else if (conf.err.id == ERROR_FILE_NOT_FOUND) {
        printf("Fichier de configuration introuvable.");
        // File not found: create default configuration.
        error default_config_creation = create_default_config(MODULE_CENTRAL);

        if (default_config_creation.id == ERROR_NONE) { // config.ini file created successfully
            printf(" Utilisation de la configuration par défaut.\n");

            // Reload the configuration we've just created.
            conf = load_config(MODULE_CENTRAL);

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
        if (strcmp(conf.pair.ip, "0.0.0.0") == 0 ||
            conf.pair.port == 0 ||
            strcmp(conf.impair.ip, "0.0.0.0") == 0 ||
            conf.impair.port == 0) {
            conf_fatal_error = TRUE;
            print_error("La configuration est invalide, veuillez contacter un administrateur.\n");
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

    char useFile = 'v';

    while(useFile != 'o' && useFile != 'O' && useFile != 'n' && useFile != 'N') {
        printf("Voulez-vous charger un fichier ? (O/N): ");
        useFile = scanfChar();
    }

    if (useFile == 'n' || useFile == 'N') {
        matrixSize = ask_lines();
    } else {
        /*char* fileName = malloc(sizeof(char*)*256);
        char* newLinePosition;
        char* afterCursor= malloc(sizeof(char*)*256);*/
        int file_read_ok = FALSE;
        //char c;

        printf("Veuillez glisser-déposer votre fichier dans cette fenêtre ");
        printf("puis cliquer sur la touche [Entrée] de votre clavier pour continuer.\n");

        while (file_read_ok == FALSE) {
            char* fileName = scanfLine();

            printf("%s\n", fileName);
            file_read fileRead = openFile(fileName);

            if (fileRead.err.id == ERROR_NONE) {
                file_read_ok = TRUE;
                // Set matrix size
                printf("OK\n");

                int i = 1;
                char* line;
                do {
                    line = readLine(fileRead);
                    if (line != NULL && strcmp(line, "") != 0) {
                        send_to_network(line, i);
                    }
                    printf("%s\n", line);
                } while(line != NULL && strcmp(line, "") != 0);
            } else {
                printf("Impossible d'ouvrir ce fichier. %s\n", fileRead.err.message);

            }

            // OU CHEMIN DU FICHIER A CHARGER
        }

    }

    printf("Taille de la matrice: [%dx%d]\n", matrixSize[0], matrixSize[1]);
    // TODO:
    // Demander les rules (rulesParser)
    ask_rules();

    // Algo final de remplacement
    // & display de Chaka
	return 0;
}