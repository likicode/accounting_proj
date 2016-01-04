#ifndef LINUX_FTP_CLIENT
#define LINUX_FTP_CLIENT


#include "utils.h"


int connect_server(char* ip, int port);

int fupdate(char* ip, int port, char *sent_fn);

int fsynchronize(char* ip, int port, char *recv_fn);


#endif
