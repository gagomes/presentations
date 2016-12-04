#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <linux/limits.h>

#include "pmls.h"

struct context {
        struct plugin_interface *input;
        struct plugin_interface *output;
        int infd;
        int outfd;
};

struct plugin_interface * load_plugin(char *filename)
{
        struct plugin_interface *plugin = NULL;
        char *err, buffer[PATH_MAX + 1] = { 0 };
        void *handle; 

        if (filename && (*filename != '/' || !strncmp(filename, "./", 2))) {
                getcwd((char *)&buffer, PATH_MAX + 1);
                strncat(buffer, "/", PATH_MAX);
                strncat(buffer, filename, PATH_MAX);
        } 

        handle = dlopen(buffer, RTLD_NOW);
        if (!handle) fatal("dlopen: %s\n", dlerror());

        plugin = (struct plugin_interface *)dlsym(handle, "interface");
        if ((err = dlerror()) != NULL) 
                fatal("dlsym");

        return plugin;
}

int main(int argc, char **argv)
{
        struct context ctx;
        char *buffer;
        size_t len;

        if (argc != 3) {
                printf("usage: %s <input_plugin> <output_plugin>\n", argv[0]);
                exit(-1);
        }

        /* open input part of the pipeline */
        ctx.input = load_plugin(argv[1]);    
        ctx.infd = ctx.input->open();

        /* open output part of the pipeline */
        ctx.output = load_plugin(argv[2]);
        ctx.outfd = ctx.output->open();

        while (1) {
                buffer = ctx.input->read(ctx.infd, &len);
                if (!buffer) {
                    break;
                }

                ctx.output->write(ctx.outfd, buffer, len);
                free(buffer);
        }

        dlclose(ctx.input);
        dlclose(ctx.output);

        return 0;
}
