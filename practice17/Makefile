CFLAGS = -Wall -g
CC = cc

all: test ex17

ex17: ex17.c
	$(CC) $(CFLAGS) ex17.c -o ex17

test: test.c stack.c stack.h
	$(CC) $(CFLAGS) stack.c test.c -o test


clean:
	rm -f  ex17 test
