## Documentation

reactor.c

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

