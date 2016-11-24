# Makefile for FISH

CC = gcc
OBJS = fish.o parse.o tolower_argv.o

fish: $(OBJS)
	$(CC) -o fish $(OBJS)

fish.o: fish.c
	$(CC) -c fish.c

parse.o: parse.c
	$(CC) -c parse.c

tolower_argv.o: tolower_argv.c
	$(CC) -c tolower_argv.c

clean:
	rm -f *.o fish