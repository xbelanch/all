CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUT=

.PHONY: test

test: main $(INPUT)
	./main $(INPUT)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
