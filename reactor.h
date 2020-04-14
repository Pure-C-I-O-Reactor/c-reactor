#ifndef REACTOR_H
#define REACTOR_H

#include <stdint.h>
#include <time.h>

typedef void (*Callback)(void *arg, int fd, uint32_t events);

typedef struct reactor Reactor;

Reactor *reactor_new(void);

int reactor_destroy(Reactor *reactor);

int reactor_register(const Reactor *reactor, int fd, uint32_t interest,
                     Callback callback, void *callback_arg);
int reactor_deregister(const Reactor *reactor, int fd);
int reactor_reregister(const Reactor *reactor, int fd, uint32_t interest,
                       Callback callback, void *callback_arg);
int reactor_run(const Reactor *reactor, time_t timeout);

#endif 
