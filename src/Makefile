# Makefile for FISH

$PROGRAM_NAME = 'fish'
$COMPILER = $(CC)

bin/$(PROGRAM_NAME): main.o
	$(CC) -o fish main.o

build/main.o: src/main.cpp
	$(CC) -o main.o -c main.cpp

clean:
	rm -f *.o fish