#include "utils.h"


int recv_file(char* fn, int socket_desc) {
    int bytes_read = 0, bytes_write = 0;
    char recved[BUFFER_SIZE];

    pthread_mutex_lock(&recv_lock);
    FILE *fp = fopen(fn, "w");

    if (fp == NULL) {
        puts("recv open failed.\n");
    }

    while ((bytes_read = recv(socket_desc, recved, BUFFER_SIZE-1, 0)) > 0) {
        recved[bytes_read] = '\0';
        if ((bytes_write = fwrite(recved, sizeof(char), bytes_read, fp)) != bytes_read) {
            perror("recv failed");
        }
    }

    fclose(fp);
    pthread_mutex_unlock(&recv_lock);

    return bytes_read;
}


int send_file(char* fn, int socket_desc) {
    int bytes_read = 0, bytes_write = 0;
    char sent[BUFFER_SIZE];

    pthread_mutex_lock(&(send_lock));
    FILE *fp = fopen(fn, "r");

    if (fp == NULL) {
        puts("send open failed.\n");
    }

    while ((bytes_read = fread(sent, sizeof(char), BUFFER_SIZE-1, fp)) > 0) {
        sent[bytes_read] = '\0';
        if((bytes_write = send(socket_desc , sent , bytes_read , 0)) < 0)
        {
            return -1;
        }
    }
    shutdown(socket_desc, SHUT_WR);

    fclose(fp);
    pthread_mutex_unlock(&send_lock);

    return bytes_read;
}
