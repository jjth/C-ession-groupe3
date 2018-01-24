#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"
#include "../globals.h"

error init_client(void) {
    error err = {
        ERROR_NONE,
        ""
    };

    error *perr = &err;
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);

    perr->id = err;
    perr->message = "Impossible de démarrer le module réseau.";
#endif
    return *perr;
}

NetworkClientConnection connect_client(const char* ip, int port) {
    error err = {
        ERROR_NONE,
        ""
    };

    NetworkClientConnection conn = {
        FALSE,
        err,
        0
    };

    error* perr = &err;
    NetworkClientConnection* pconn = &conn;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    struct hostent *hostinfo;

    if(sock == INVALID_SOCKET){
        perr->id = errno;
        perr->message = strerror(errno);
    }

    hostinfo = gethostbyname(ip);
    if (hostinfo == NULL){
        perr->id = ERROR_HOST_UNKNOWN;
        perr->message = "Ce nom de domaine est inconnu.";
    } else {
        sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
        sin.sin_port = htons(port);
        sin.sin_family = AF_INET;

        if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR){
            perr->id = ERROR_HOST_DOWN;
            perr->message = "Cannot connect to the server.";
        } else {
            pconn->connected = TRUE;
        }
    }

    pconn->socket = sock;
    pconn->err = *perr;

    return *pconn;
}

void deinit_client() {
#if defined(WIN32) || defined(WIN32) || (defined(CYGWIN_) && !defined(_WIN32))
    WSACleanup();
#endif
}

error send_to_network(NetworkClientConnection conn, const char* line) {
    error err = {ERROR_NONE, ""};
    error* perr = &err;
    printf("%d\n", conn.socket);
    if(send(conn.socket, line, strlen(line), 0) < 0) {
        perr->id = errno;
        perr->message = strerror(errno);
    } else {
        printf("Line sent.\n");
    }

    return *perr;
}
