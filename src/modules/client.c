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

error send_to_network(NetworkClientConnection conn, char* line) {
    error err = {ERROR_NONE, ""};
    error* perr = &err;

    if(send(conn.socket, line, strlen(line), 0) < 0) {
        perr->id = errno;
        perr->message = strerror(errno);
    } else {
        //printf("Command sent.\n");
    }

    return *perr;
}

error send_line_to_network(NetworkClientConnection conn, char* line) {
    return send_to_network(conn, prepare_for_send(CMD_SEND_LINE, line));
}

char* receive_data(NetworkClientConnection conn, int size) {
    int n = 0;
    size = 256;
    if (size > 0) {
        char* buffer = malloc(sizeof(char*)*size);

        // ERROR: Impair won't answer, but why ?
        if((n = recv(conn.socket, buffer, size, 0)) < 0){
            perror("recv()");
            return "\0";
        }

        //printf("buffer : %s\n", buffer);
        return buffer;
    } else {
        return "\0";
    }
}

int set_color_from(NetworkClientConnection conn, int x, int y, int c) {
    char command[50];

    sprintf(command, "%d;%d;%c", x, y,c);
    error err = send_to_network(conn, prepare_for_send(CMD_SET_COLOR, command));

    if (err.id != ERROR_NONE) {
        return 0;
    } else {
        char* data = receive_data(conn, 1);
        return data[0];
    }
}

char set_char_from(NetworkClientConnection conn, int x, int y, char c) {
    char command[50];

    sprintf(command, "%d;%d;%c", x, y,c);
    error err = send_to_network(conn, prepare_for_send(CMD_SET_CHAR, command));

    if (err.id != ERROR_NONE) {
        return 0;
    } else {
        char* data = receive_data(conn, 1);
        return data[0];
    }
}

char get_char_from(NetworkClientConnection conn, int x, int y) {
    char command[50];

    sprintf(command, "%d;%d", x, y);
    error err = send_to_network(conn, prepare_for_send(CMD_GET_CHAR, command));

    printf("GET_CHAR_FROM\n");
    if (err.id != ERROR_NONE) {
        return 0;
    } else {
        char* data = receive_data(conn, 1);
        printf("RECV: '%s'\n", data);
        return data[0];
    }
}

int get_color_from(NetworkClientConnection conn, int x, int y) {
    char command[50];

    sprintf(command, "%d;%d", x, y);
    error err = send_to_network(conn, prepare_for_send(CMD_GET_COLOR, command));

    if (err.id != ERROR_NONE) {
        return 0;
    } else {
        char* data = receive_data(conn, 1);
        return (int) data[0];
    }
}

char* set_new_cycle(NetworkClientConnection conn) {
    error err = send_to_network(conn, prepare_for_send(CMD_TIME_NEW, ""));

    if (err.id != ERROR_NONE) {
        return 0;
    } else {
        return receive_data(conn, 2);
    }
}
