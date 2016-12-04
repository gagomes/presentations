CC = gcc
LD = ld
CFLAGS = -Wall -g3 -ggdb
LDFLAGS =  -shared -fPIC
LIBNAME	= libhelloworld.so
APPNAME = app

all: lib binary

lib:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIBNAME) libhelloworld.c

binary:
	$(CC) $(CFLAGS) $(APPNAME).c -o $(APPNAME) -I . -l helloworld -L .

clean:
	rm -rf core *~ $(LIBNAME) 
