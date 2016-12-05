#ifndef __PMLS_H__
#define __PMLS_H__

// Plugin interface

struct plugin_interface {
	int (*open)();
    	void *(*read)(int fd, size_t *len);
	int (*write)(int fd, void *buffer, size_t len);
};

#define fatal(x, ...) { fprintf(stderr, "fatal: "); fprintf(stderr, x, ##__VA_ARGS__); exit(EXIT_FAILURE); }

#endif
