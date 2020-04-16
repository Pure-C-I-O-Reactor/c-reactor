## Documentation

### reactor.c

Adding reactor into hash-table of sockets and event processers in system selector

```
1. int reactor_register(const Reactor *reactor, int fd, uint32_t interest,
                     Callback callback, void *callback_arg)
```

Removing reactor and updating socket list and event processers in system selector and hash-table

```
2. int reactor_deregister(const Reactor *reactor, int fd)
```

Modifiying the reactor in the hash-table

```
3. int reactor_reregister(const Reactor *reactor, int fd, uint32_t interest,
                       Callback callback, void *callback_arg)
```

Find argument reactor in the table, and destroy it, also remove from g_list by its descriptor and free the memory

```
4. int reactor_destroy(Reactor *reactor)
```

After the I / O reactor intercepted the event with the fd descriptor, it calls the corresponding event handler, into which it passes fd, the bit mask of the generated events, and the user pointer to void.

```
5. int reactor_run(const Reactor *reactor, time_t timeout)
```

### reactor.h


Pointer to the function, that is called by I/O reactor when event received from sys.selector
```
1. typedef void (*Callback)(void *arg, int fd, uint32_t events);
```
Creating new struct of Reactor
```
2. typedef struct reactor Reactor;
```

If we receive NULL - some error, otherwise pointer to our reactor
```
3. Reactor *reactor_new(void);
```
All below methods are response -1 if some error and 0 in case of success. 
They are responsible for reactor's functionality. 
```
4. int reactor_destroy(Reactor *reactor);

int reactor_register(const Reactor *reactor, int fd, uint32_t interest,
                     Callback callback, void *callback_arg);
int reactor_deregister(const Reactor *reactor, int fd);
int reactor_reregister(const Reactor *reactor, int fd, uint32_t interest,
                       Callback callback, void *callback_arg);
```
Here we are starting our reactor with timer timeout.
This function will give control to the calling if the allotted time has elapsed or an error of sockets.

```
5. int reactor_run(const Reactor *reactor, time_t timeout);
```