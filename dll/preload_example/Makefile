CC = gcc
CFLAGS = -Wall -ggdb -g3 -fPIC -I .
LDFLAGS = -ldl -nostartfiles -shared 
OBJS = preload1.o
LIB = preload1.so

all: $(OBJS)
	@#gcc pl1.c -o pli.so -shared -fPIC -g3 -ggdb -ldl -nostartfiles -I.
	$(CC) -o $(LIB) $(OBJS) $(LDFLAGS)

test:
	@LD_PRELOAD=${PWD}/$(LIB) ls

clean:
	rm -rf $(OBJS) $(LIB) core* *~
