#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "server.h"

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

void app(int port){
	SOCKET sock = init_connection(port);
	char buffer[BUF_SIZE];
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

void write_client(SOCKET sock, const char *buffer){
	if(send(sock, buffer, strlen(buffer), 0) < 0){
		perror("send()");
		exit(errno);
	}
}
