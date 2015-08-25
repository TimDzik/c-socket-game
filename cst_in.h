#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CHECK(sts, msg)                \
    if ((sts) == -1) {                \
        perror(msg);                \
        exit(-1);                    \
    }

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_SVC "/tmp/socket_svc"

#define MAXBUFF 1024
