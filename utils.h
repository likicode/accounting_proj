#ifndef LINUX_FTP_UTILS
#define LINUX_FTP_UTILS


#include <time.h>
#include <stdio.h>
#include <libgen.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include "stype.h"


#define BUFFER_SIZE 2048


pthread_mutex_t recv_lock;
pthread_mutex_t send_lock;

int recv_file(char* fn, int socket_desc);

int send_file(char* fn, int socket_desc);


#endif
