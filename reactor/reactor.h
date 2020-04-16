#ifndef REACTOR_H
#define REACTOR_H

#include <stdint.h>
#include <time.h>

// Pointer to the function, that is called by I/O reactor when event received from sys.selector
typedef void (*Callback)(void *arg, int fd, uint32_t events);

// Creating new struct of Reactor
typedef struct reactor Reactor;

// If we receive NULL - some error
// Otherwise pointer to our reactor
Reactor *reactor_new(void);

/*
	All below methods are response -1 if some error and 0 in case of success.
	They are responsible for reactor's functionality. 
*/
int reactor_destroy(Reactor *reactor);

int reactor_register(const Reactor *reactor, int fd, uint32_t interest,
                     Callback callback, void *callback_arg);
int reactor_deregister(const Reactor *reactor, int fd);
int reactor_reregister(const Reactor *reactor, int fd, uint32_t interest,
                       Callback callback, void *callback_arg);

/*
	Here we are starting our reactor with timer timeout.
	This function will give control to the calling 
	 if the allotted time has elapsed or an error of sockets.
*/
int reactor_run(const Reactor *reactor, time_t timeout);

#endif 