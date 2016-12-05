#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#include "pmls.h"

int stdin_open() 
{
#ifndef __PMLS_BLOCK_ON_STDIN__
        return fileno(stdin);
#else
        return open("/dev/stdin", O_NONBLOCK);
#endif

}    

void *stdin_read(int fd, size_t *len)
{
        int rc, rsize = 4096;
        char *buffer;

        *len = 0;
        buffer = malloc(rsize);
        if (!buffer) fatal("Out of memory\n");

        memset(buffer, 0x0, rsize);

        rc = read(fd, buffer, rsize - 1);
        if (rc < 0) {
                fatal("read: %s\n", strerror(errno));
        } else if (rc == 0) {
                /* EOF */ 
                free(buffer);
                return NULL;
        } else {
                *len = rc;
        }

        return buffer;
}

struct plugin_interface interface = {
    .open = &stdin_open,
    .read = &stdin_read,
    .write = NULL,
};
