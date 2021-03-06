#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "globals.h"
#include "modules/configparser.h"
#include "modules/colors.h"
#include "modules/client.h"
#include "modules/readLines.h"
#include "modules/rulesParser.h"
#include "modules/readFile.h"
#include "modules/scanf.h"
#include "modules/applyRules.h"
#include "modules/displayMatrix.h"

#define LINE_SIZE 5
#define NB_LINE 5

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

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

    int pairConnectionOK = FALSE;
    int impairConnectionOK = FALSE;

    conn_pair = connect_client(conf.pair.ip, conf.pair.port);
    //conn_impair = connect_client(conf.pair.ip, conf.pair.port);
    conn_impair = conn_pair;

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
                //conn_impair = connect_client(conf.impair.ip, conf.impair.port);
                conn_impair = conn_pair;
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

    int* matrixSize;

    char useFile = 'v';

    while(useFile != 'o' && useFile != 'O' && useFile != 'n' && useFile != 'N') {
        printf("Voulez-vous charger un fichier ? (O/N): ");
        useFile = scanfChar();
    }

    if (useFile == 'n' || useFile == 'N') {
        matrixSize = ask_lines(&conn_pair, &conn_impair);
    } else {
        matrixSize = malloc(sizeof(int)*2);
        int file_read_ok = FALSE;

        printf("Veuillez glisser-déposer votre fichier dans cette fenêtre ");
        printf("puis cliquer sur la touche [Entrée] de votre clavier pour continuer.\n");

        while (file_read_ok == FALSE) {
            char* fileName = scanfLine();

            file_read fileRead = openFile(fileName);

            if (fileRead.err.id == ERROR_NONE) {
                file_read_ok = TRUE;

                int i = 1;
                char* line;
                NetworkClientConnection conn_temp;
                error err;
                do {
                    line = readLine(fileRead);
                    if (line != NULL && strcmp(line, "") != 0) {
                        if (i%2 == 0) {
                            conn_temp = conn_pair;
                        } else {
                            conn_temp = conn_impair;
                        }

                        err = send_line_to_network(conn_temp, line);

                        if (err.id != ERROR_NONE) {
                            printf("Impossible d'envoyer la ligne %d : %s\n", i, err.message);
                            // Failed ? Try again one more time.
                            err = send_line_to_network(conn_temp, line);

                            if (err.id != ERROR_NONE) {
                                // Failed again, we gotta crash now
                                printf("Impossible d'envoyer la ligne %d : %s\n", i, err.message);
                                exit(1);
                            }
                        }

                        i++;
                    }

                } while(line != NULL && strcmp(line, "") != 0);
                matrixSize[0] = fileRead.column_count;
                matrixSize[1] = i-1;
            } else {
                printf("Impossible d'ouvrir ce fichier. %s\n", fileRead.err.message);

            }
        }
    }

    printf("Taille de la matrice: [%dx%d]\n", matrixSize[0], matrixSize[1]);

    llist* rules = ask_rules();

    char continueRunning = 'o';
    int currentCycle = 0;
    int numberOfCycles = 1;

    printf("Voulez-vous faire défiler manuellement le temps ? (O/N) : ");
    char c = 'x';
    
    while (c != 'o' && c != 'O' && c != 'n' && c!= 'N')
        c = scanfChar();

    if (c == 'o' || c == 'O') {
        numberOfCycles = 1;
    } else {
        printf("Combien de cycles voulez-vous passer ? ");

        int i = -1;
        
        while (i < 1) i = scanfInt();

        numberOfCycles = i;
    }

    printf("\nVous avez choisi %d cycle(s).\n", numberOfCycles);
        
    while (continueRunning == 'o' || continueRunning == 'O') {
        currentCycle = 0;
        while(currentCycle < numberOfCycles) {
            Ope *myOpe = malloc(sizeof(*myOpe));
            //int isApplied = 0;
            myOpe->ope1 = -1;
            myOpe->ope2 = -1;
            myOpe->operator = -1;

            NetworkClientConnection conn_temp;
            //get_char_from
            // Algo final de remplacement
            // & display de Chaka
            //printf("BONJOUR\n");
            for (int i = 0; i<matrixSize[0]; i++) {
                for (int o = 0; o<matrixSize[1]; o++) {
                    if ((i % 2) == 0) conn_temp = conn_pair;
                    else conn_temp = conn_impair;

                    element *tmp=rules->first;
                    while(tmp != NULL){
                        if(tmp->rule->charA == get_char_from(conn_temp, i, o)){
                            if(check_rule(i,o,tmp->rule,myOpe,matrixSize[0], matrixSize[1]) == 1){
                                set_char_from(conn_temp, i, o, tmp->rule->charG);
                                set_color_from(conn_temp, i, o, tmp->color);
                            }

                            tmp = tmp->nxt;
                        }
                    }
                }
            }

            display_matrix(matrixSize[0], matrixSize[1]);
            //printf("BONJOURCHAKA 1\n");
            char* a = set_new_cycle(conn_pair);
            //printf("BONJOURCHAKA\n");
            //char* b = set_new_cycle(conn_impair);

            //if(strcmp(a,b) == 0 && strcmp(a,"OK") != 0) {
            if (strcmp(a, "OK") != 0) {
                printf("Un cycle à été détecté à T%s\n", a);
                return 0;
            }
            currentCycle++;
        }

        printf("\nContinuer ? (O/N) ");
        continueRunning = scanfChar();
    }
        
	return 0;
}
