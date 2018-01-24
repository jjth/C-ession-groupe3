#ifndef SERVER_H
#define SERVER_H

#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
#define WIN32 0
#include <windows.h>

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
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#define CRLF		"\r\n"

#define BUF_SIZE	1024


void init(void);
void end(void);
void app(int port);
int init_connection(int port);
int read_client(SOCKET* sock, char *buffer);
void write_client(SOCKET sock, const char *buffer);

#endif /* guard */