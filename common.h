#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "reactor.h"


#define SERVER_PORT 18470
#define SERVER_IPV4 "127.0.0.1"
#define SERVER_BACKLOG 1024
#define SERVER_TIMEOUT_MILLIS 1000 * 60

#define REQUEST_BUFFER_CAPACITY 1024

#define CRLF "\r\n"
#define DOUBLE_CRLF CRLF CRLF
#define DOUBLE_CRLF_LEN strlen(DOUBLE_CRLF)


#define SAFE_CALL(call, error)                                                 \
    do {                                                                       \
        if ((call) == error) {                                                 \
            fail("%s", #call);                                                 \
        }                                                                      \
    } while (false)

static void on_accept(void *arg, int fd, uint32_t events);

static void on_send(void *arg, int fd, uint32_t events);

static void on_recv(void *arg, int fd, uint32_t events);

static void set_nonblocking(int fd);

static noreturn void fail(const char *format, ...);

static int new_server(bool reuse_port);

