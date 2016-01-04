#include "utils.h"
#include "file_client.h"


int connect_server(char* ip, int port) {
    int socket_desc;
    struct sockaddr_in server;

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
 
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return -1;
    }

    return socket_desc;
}


int fupdate(char* ip, int port, char *sent_fn) {
    int socket_desc;

    if ((socket_desc = connect_server(ip, port)) == -1) {
        puts("connect error");
        return -1;
    }

    if(send(socket_desc , "update", 7 , 0) != 7) {
        puts("update error.\n");
        return -1;
    }

    send_file(sent_fn, socket_desc);

    close(socket_desc);

    return 0;
}


int fsynchronize(char* ip, int port, char *recv_fn) {
    int socket_desc;

    if ((socket_desc = connect_server(ip, port)) == -1) {
        puts("connect error");
        return -1;
    }

    if(send(socket_desc , "sync", 5 , 0) != 5) {
        perror("sync error.\n");
        return -1;
    }

    recv_file(recv_fn, socket_desc);
    close(socket_desc);

    return 0;
}
