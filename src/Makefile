# Makefile for FISH

CC = gcc
OBJS = fish.o parse.o

fish: $(OBJS)
	$(CC) -o fish $(OBJS)

fish.o: fish.c
	$(CC) -c fish.c

parse.o: parse.c
	$(CC) -c parse.c

clean:
	rm -f *.o fish