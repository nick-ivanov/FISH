# Makefile for mnsh

mnsh: main.o
	gcc -o mnsh main.o

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o mnsh
