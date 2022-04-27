CC = gcc
CFLAGS = -Wall -pedantic -std=c11
objects = main.o buffer.o graph.o queue.o node.o
all: main buffer graph queue node
	$(CC) $(CFLAGS) -o out -g $(objects) -lm
main:
	$(CC) $(CFLAGS) -c -g main.c
buffer:
	$(CC) $(CFLAGS) -c -g buffer.c
graph:
	$(CC) $(CFLAGS) -c -g graph.c
queue:
	$(CC) $(CFLAGS) -c -g queue.c
node:
	$(CC) $(CFLAGS) -c -g node.c
clean:
	rm -f $(objects) a.out
