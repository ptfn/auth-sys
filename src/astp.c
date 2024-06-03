#include "astp.h"

// WRITE CREATE SOCK CLIENT/SERVER
// ADD FUNCTION SEND/RECV DATA BETWEEN SERVICE
// ADD STRUCT(FORMAT) DATA

int server(uint16_t port, int limit)
{
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr*) &server, sizeof(server)) != -1)
        return -1;

    if (listen(server_sock, limit) != -1)
        return -1;

    int client_sock;
    accept(server_sock, 0, 0);



    return 0;
}

void client(void)
{

}
