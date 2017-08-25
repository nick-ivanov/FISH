# Makefile for FISH

CC = gcc
OBJS = fish.o fish_parse.o fish_tolower_argvx.o fish_help.o fish_run.o fish_quit.o fish_launch.o fish_list.o fish_copy.o fish_remove.o fish_cd.o fish_show.o fish_mkdir.o fish_rmdir.o

fish: $(OBJS)
	$(CC) -o fish $(OBJS)

fish.o: fish.c
	$(CC) -c fish.c

fish_parse.o: fish_parse.c
	$(CC) -c fish_parse.c

fish_tolower_argvx.o: fish_tolower_argvx.c
	$(CC) -c fish_tolower_argvx.c

fish_help.o: fish_help.c
	$(CC) -c fish_help.c

fish_run.o: fish_run.c
	$(CC) -c fish_run.c

fish_quit.o: fish_quit.c
	$(CC) -c fish_quit.c

fish_launch.o: fish_launch.c
	$(CC) -c fish_launch.c

fish_list.o: fish_list.c
	$(CC) -c fish_list.c

fish_copy.o: fish_copy.c
	$(CC) -c fish_copy.c

fish_remove.o: fish_remove.c
	$(CC) -c fish_remove.c

fish_cd.o: fish_cd.c
	$(CC) -c fish_cd.c

fish_show.o: fish_show.c
	$(CC) -c fish_show.c	

fish_mkdir.o: fish_mkdir.c
	$(CC) -c fish_mkdir.c

fish_rmdir.o: fish_rmdir.c
	$(CC) -c fish_rmdir.c

clean:
	rm -f *.o fish