# Makefile for FISH

$CC = gcc

fish: fish.o
	$(CC) -o fish fish.o

fish.o: fish.c
	$(CC) -c fish.c

clean:
	rm -f *.o fish