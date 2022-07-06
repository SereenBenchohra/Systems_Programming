#ifndef MINICHATH
#define MINICHATH

#include <arpa/inet.h>
#include <getopt.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>


#define MAXLINE 1024
#define MAX_CONNECTIONS 100

void server_init(char *portName);
void client_init(char *hostname, char *portName);
#endif
