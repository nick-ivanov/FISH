# Makefile for FISH

$CC = gcc

$(PROGRAM_NAME): fish.o
	$(CC) -o fish fish.o

fish.o: fish.c
	$(CC) -o fish.o -c fish.c

clean:
	rm -f *.o fish