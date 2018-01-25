#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "dataStructure.h"
#include "../globals.h"
#include "server.h"

int globalCptTime = 0;
int globalCptLine = 0;
int globalSizeLine = 0;


void init(void){
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

void end(void){
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
   WSACleanup();
#endif
}

void app(int port, ModuleType module){
	SOCKET sock = init_connection(port);
	char buffer[BUF_SIZE];
	int line = 5; 
    int col = 3;
    int d = 3;
    char t = 'X';
    int nbLine = 5;
    int nbColunm = 4;
	ListingLine *myListing = initialisationLine();
    if(module == MODULE_PAIR) globalCptLine = 2;
	else globalCptLine = 1;
    displayListingValue(myListing,4);
    /*deleteALine(myListing,0);
    displayListing(myListing,4);
    setCharacter(myListing, 2,3,'z');
    displayListing(myListing,4);
    printf("%c \n",getCharacter(myListing, 2,3));
    */printf("%d \n",getCharacterColor(myListing, 2,3));
    /*setCharacterColor(myListing,2,3,2);
    displayListing(myListing,4);*/
    printf("x: %d, y: %d [%c], d: %d, t: %c, result:%d \n",col,line,getCharacter(myListing,line,col),d,t,getNeighbors(myListing,nbLine,nbColunm,line,col,d,t));

	/* the index for the array */
	SOCKADDR_IN csin = { 0 };
	socklen_t sinsize = sizeof csin;

	while(1) {
		int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
		printf("[-] Nouvelle connection\n");
		/* what is the new maximum fd ? */
		//max = csock > max ? csock : max;

		while(1){
			int c = read_client(&csock, buffer);
			/* client disconnected */
			if(c == 0){
				closesocket(csock);
				break;
			} 

			write_client(csock, "Ok serv 1");
		}
	}
}


int init_connection(int port){
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

int read_client(SOCKET* sock, char *buffer){
	// TODO : A REVOIR DANS LE SWITCH
	int n = 0;
	char* cmd;
	char** data;
	int sizeLine = 0;
	char result_char;
	int result_color; 
	if((n = recv(*sock, buffer, BUF_SIZE - 1, 0)) < 0){
		perror("recv()");
		/* if recv error we disonnect the client */
		n = 0;
	}
	buffer[n] = 0;
	// printf("%s \n", buffer);
	cmd = get_command(buffer);
	switch(cmd){
		case CMD_SEND_LINE :
			if(globalSizeLine == 0){
				sizeLine = strlen(get_recv_data(buffer));
				globalSizeLine = sizeLine;
			}
			addALine(??, globalSizeLine,globalCptLine,get_recv_data(buffer));
			globalCptLine+=2;
			break;
		case CMD_RESET :
			//TODO : FREE de tout ici
			break;
		case CMD_GET_CHAR : 
			data = str_split(get_recv_data(buffer));
			result_char = getCharacter(??,atoi(data[0]), atoi(data[1]));
			write_client(sock, result_char);
			break;
		case CMD_SET_CHAR, : 
			data = str_split(get_recv_data(buffer));		
			setCharacter(??,atoi(data[0]), atoi(data[1]), data[2]);
			break;
		case CMD_GET_COLOR : 
 			data = str_split(get_recv_data(buffer));
			result_color = getCharacterColor(??, atoi(data[0]),atoi(data[1]));
			write_client(sock, itoa(result_color));
			break;
		case CMD_SET_COLOR, : 
			data = str_split(get_recv_data(buffer));
			setCharacterColor(??,atoi(data[0]),atoi(data[1]), atoi(data[2]));
			break;
		case CMD_TIME_NEW : 
			globalCptTime++;
			// créer un nouveau T et mettre en queue du prèc 
			break;
		case CMD_UNKNOWN : 
			// TODO 
			break;
	}
	
	return n;
}

void write_client(SOCKET sock, const char *buffer){
	if(send(sock, buffer, strlen(buffer), 0) < 0){
		perror("send()");
		exit(errno);
	}
}
