# Makefile for FISH

$PROGRAM_NAME = 'fish'
$COMPILER = $(CC)

$(PROGRAM_NAME): main.o
	$(CC) -o fish main.o

build/main.o: main.c
	$(CC) -o main.o -c main.cpp

clean:
	rm -f *.o fish