CC = gcc
CFLAGS = -Wall -g3 -ggdb -I .
LDFLAGS =

all: clean plugins pmls

pmls: 
	$(CC) $(CFLAGS) -o pmls pmls.c -ldl

plugins:
	gcc $(CFLAGS) -shared -fPIC -o stdin.so stdin.c
	gcc $(CFLAGS) -shared -fPIC -o stdout.so stdout.c

clean:
	rm -rf core pmls *~ stdin.so stdout.so
