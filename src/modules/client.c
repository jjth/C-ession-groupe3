#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"

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

static void app(const char *address1, const char *address2){
    SOCKET sockPair = init_connection(address2, 767);
    SOCKET sockImpair = init_connection(address1, 766);
    char buffer[BUF_SIZE];
    char buffer2[BUF_SIZE];
    while(1){
      /* something from standard input : i.e keyboard */
        fgets(buffer, BUF_SIZE - 1, stdin);
        {
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL){
                *p = 0;
            }else{
                /* fclean */
                buffer[BUF_SIZE - 1] = 0;
            }
         }
        write_server(sockPair, buffer);
        write_server(sockImpair, buffer);        

        int n = read_server(&sockPair, buffer);
        int n1 = read_server(&sockImpair, buffer2);        

        /* server down */
        if(n == 0){
            printf("Server disconnected !\n");
            break;
        }
        if(n1 == 0){
            printf("Server disconnected !\n");
            break;
        }
        puts(buffer);
        puts(buffer2);
   }

   closesocket(sockImpair);
   closesocket(sockPair);
   
}

static int init_connection(const char *address, int port){
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET){
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL){
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR){
      perror("connect()");
      exit(errno);
   }

   return sock;
}

static int read_server(SOCKET* sock, char *buffer){
   int n = 0;
    printf("recv\n");
    if((n = recv(*sock, buffer, BUF_SIZE - 1, 0)) < 0){
        perror("recv()");
        exit(errno);
    }
   buffer[n] = 0;

   return n;
}

static void write_server(SOCKET sock, const char *buffer){
    if(send(sock, buffer, strlen(buffer), 0) < 0){
        perror("send()");
        exit(errno);
    }
}

int main(int argc, char **argv){

    char* adr1;
    char* adr2;
    adr1 = "127.0.0.1";
    adr2 = "127.0.0.1";

    init();

    app(adr1, adr2);

    end();

    return EXIT_SUCCESS;
}