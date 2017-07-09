# Makefile for FISH

CC = gcc
OBJS = fish.o parse.o tolower_argvx.o help.o run.o quit.o launch.o list.o copy.o remove.o cd.o

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

quit.o: quic.c
	$(CC) -c quit.c

launch.o: launch.c
	$(CC) -c launch.c

list.o: list.c
	$(CC) -c list.c

copy.o: copy.c
	$(CC) -c copy.c

remove.o: remove.c
	$(CC) -c remove.c

cd.o: cd.c
	$(CC) -c cd.c

show.o: show.c
	$(CC) -c show.c	

clean:
	rm -f *.o fish