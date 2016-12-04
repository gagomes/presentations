#include <stdio.h>
#include <unistd.h>

#include "pmls.h"

int stdout_open() 
{
        return fileno(stdout);
}    

void *stdout_read(int fd, size_t *len)
{
    return (void *)0;
}

int stdout_write(int fd, void *buffer, size_t len)
{
        return write(fd, buffer, len);
}

struct plugin_interface interface = {
    .open = &stdout_open,
    .read = &stdout_read,
    .write = &stdout_write
};
