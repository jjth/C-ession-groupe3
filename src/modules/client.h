#ifndef CLIENT_H
#define CLIENT_H

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#define CRLF	 "\r\n"
#define PORT	 766
#define BUF_SIZE 1024
#include "../globals.h"

error init_client(void);
NetworkClientConnection connect_client(const char* ip, int port);
void deinit_client();
error send_to_network(NetworkClientConnection conn, char* line);
error send_line_to_network(NetworkClientConnection conn, char* line);
char* set_new_cycle(NetworkClientConnection conn);
char get_char_from(NetworkClientConnection conn, int x, int y);
int get_color_from(NetworkClientConnection conn, int x, int y);
#endif /* guard */