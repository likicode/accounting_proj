#include "utils.h"


int recv_file(char* fn, int socket_desc) {
    int bytes_read = 0, bytes_write = 0;
    char recved[BUFFER_SIZE];

    pthread_mutex_lock(&recv_lock);
    FILE *fp = fopen(fn, "w");

    if (fp == NULL) {
        puts("recv open failed.\n");
        pthread_mutex_unlock(&recv_lock);
        return -1;
    }

    while ((bytes_read = recv(socket_desc, recved, sizeof(recved), 0)) > 0) {
        if (recved[bytes_read-1] == '#') {
            bytes_read -= 1;
            bytes_write = fwrite(recved, sizeof(char), bytes_read, fp);
            break;
        } else {
            bytes_write = fwrite(recved, sizeof(char), bytes_read, fp);
        }

        if (bytes_write != bytes_read) {
            puts("recv error.\n");
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
        pthread_mutex_unlock(&send_lock);
        return -1;
    }

    while ((bytes_read = fread(sent, sizeof(char), BUFFER_SIZE, fp)) > 0) {
        if((bytes_write = send(socket_desc , sent , bytes_read , 0)) < 0)
        {
            return -1;
        }
    }
    // sleep(1);
    // shutdown(socket_desc, SHUT_WR);
    send(socket_desc , "#" , 1 , 0);

    fclose(fp);
    pthread_mutex_unlock(&send_lock);

    return bytes_read;
}
