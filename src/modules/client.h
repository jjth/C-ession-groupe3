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
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#define CRLF	 "\r\n"
#define PORT	 766
#define BUF_SIZE 1024

static void init(void);
static void end(void);
static void app(const char *address1,const char *address2);
static int init_connection(const char *address1,int port);
static int read_server(SOCKET* sock, char *buffer);
static void write_server(SOCKET sock, const char *buffer);

#endif /* guard */