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

#define LINE_SIZE 5
#define NB_LINE 5

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#define Sleep(x) usleep((x)*1000)
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
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

    char useFile = 'v';

    while(useFile != 'o' && useFile != 'O' && useFile != 'n' && useFile != 'N') {
        printf("Voulez-vous charger un fichier ? (O/N): ");
        scanf("%c", &useFile);
    }

    if (useFile == 'n' || useFile == 'N') {
        matrixSize = ask_lines();
    } else {
        char* fileName = malloc(sizeof(char*)*256);
        char* newLinePosition;
        char* afterCursor= malloc(sizeof(char*)*256);
        int file_read_ok = FALSE;
        char c;

        printf("Veuillez glisser-déposer votre fichier dans cette fenêtre ");
        printf("puis cliquer sur la touche [Entrée] de votre clavier pour continuer.\n");

        while (file_read_ok == FALSE) {
            // Empty input buffers;
            c = getchar();
            fileName[0] = '\0';
            int i = 0;
            int cursorPos = i;
            // While the user didn't type a correct file name.
            do {
                int skipChar = FALSE;
                c = getch();
                if (c == 127) {
                    if (cursorPos > 0) {
                        int o = 0;
                        int u = 0;
                        int addedChars = 0;
                        printf("\b");
                        while (o < i && fileName[o] != '\0' && o < 255) {
                            fileName[u] = fileName[o];

                            if (o != (cursorPos -1)) {
                                if (u < o) {
                                    printf("%c", fileName[u]);
                                    addedChars += 1;
                                }
                                u=u+1;
                            }

                            o=o+1;
                        }

                        printf("%c\b ", fileName[u]);

                        for (o = addedChars; o >= 0; o--) {
                            printf("\b");
                        }                        
                        i -= 1;
                        cursorPos -= 1;
                        fileName[i] = '\0';
                    }
                    skipChar = TRUE;
                } else if (c == 27) {
                    c = getch();
                    if (c == 91) {
                        c = getch();
                        if (c > 64 && c < 69) {
                            if (c == 67 && cursorPos < i) {
                                cursorPos += 1;
                                printf("\033[1C");
                            } else if (c == 68 &&cursorPos > 0 ) {
                                cursorPos -= 1;
                                printf("\033[1D");
                            }

                            skipChar = TRUE;
                        }
                    }
                }

                if (i < 256 && skipChar == FALSE && c != '\n') {
                    putchar(c);

                    int u = 0;
                    int o = 0;
                    
                    if (cursorPos == i) {
                        fileName[i] = c;
                    } else {
                        char* newFilename = malloc(sizeof(char*)*256);
                        strcpy(newFilename, fileName);

                        u = 0;
                        o = 0;
                        
                        while(o <= i) {
                            newFilename[u] = fileName[o];

                            if (o == cursorPos) {
                                newFilename[u+1] = fileName[o];

                                newFilename[u] = c;

                                u++;
                            }

                            if (u > o) {
                                putchar(newFilename[u]);
                            }

                            u++;
                            o++;
                        }

                        for (o = o; o > cursorPos; o--) {
                            printf("\b");
                        }
                        free(fileName);
                        fileName = newFilename;
                    }


                    cursorPos += 1;
                    i=i+1;
                }

            //printf("FILE: %s\n", fileName);
            } while(c != EOF && c != '\n');
            free(afterCursor);
            printf("\n");
            
            file_read fileRead = openFile(fileName);

            if (fileRead.err.id == ERROR_NONE) {
                file_read_ok = TRUE;
                // Set matrix size
            } else {
                printf("Impossible d'ouvrir ce fichier. %s\n", fileRead.err.message);

                int i = 1;
                char* line;
                do {
                    line = readLine(fileRead);
                    if (line != NULL && strcmp(line, "") != 0) {
                        send_to_network(line, i);
                    }
                    
                } while(line != NULL && strcmp(line, "") != 0);
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