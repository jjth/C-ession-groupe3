#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "configparser.h"
#include "server.h"
#include "colors.h"

void print_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    setColor(1); // 1 = RED (see ANSI color codes)
    printf(format, args);
    resetColor();

    va_end(args);
}

static void init(void){
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
   WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
	  puts("WSAStartup failed !");
	  exit(EXIT_FAILURE);
   }
#endif
}

static void end(void){
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
   WSACleanup();
#endif
}

static void app(int port){
	SOCKET sock = init_connection(port);
	char buffer[BUF_SIZE];
	/* the index for the array */
	int max = sock;

	SOCKADDR_IN csin = { 0 };
	size_t sinsize = sizeof csin;
	int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
	printf("[-] Nouvelle connection\n");
	/* what is the new maximum fd ? */
	//max = csock > max ? csock : max;

	while(1){
		int i = 0;
		int c = read_client(&csock, buffer);
		/* client disconnected */
		if(c == 0){
			closesocket(csock);
			break;
		} 

		write_client(csock, "Ok serv 1");

	}

}


static int init_connection(int port){
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = { 0 };

	if(sock == INVALID_SOCKET){
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR){
		perror("bind()");
		exit(errno);
	}

	if(listen(sock, 1) == SOCKET_ERROR){
		perror("listen()");
		exit(errno);
	}

	return sock;
}

static int read_client(SOCKET* sock, char *buffer){
	int n = 0;

	if((n = recv(*sock, buffer, BUF_SIZE - 1, 0)) < 0){
		perror("recv()");
		/* if recv error we disonnect the client */
		n = 0;
	}
	buffer[n] = 0;
	printf("%s \n", buffer);
	return n;
}

static void write_client(SOCKET sock, const char *buffer){
	if(send(sock, buffer, strlen(buffer), 0) < 0){
		perror("send()");
		exit(errno);
	}
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
	
	app(conf.client.port);

	end();

	return EXIT_SUCCESS;
}