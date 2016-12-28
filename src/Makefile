# Makefile for FISH

CC = gcc
OBJS = fish.o parse.o tolower_argvx.o help.o run.o

fish: $(OBJS)
	$(CC) -o fish $(OBJS)

fish.o: fish.c
	$(CC) -c fish.c

parse.o: parse.c
	$(CC) -c parse.c

tolower_argvx.o: tolower_argvx.c
	$(CC) -c tolower_argvx.c

help.o: help.c
	$(CC) -c help.c

run.o: run.c
	$(CC) -c run.c

clean:
	rm -f *.o fish