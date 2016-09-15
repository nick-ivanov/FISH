# Makefile for mnsh

bin/mnsh: build/main.o
	gcc -o bin/mnsh build/main.o

build/main.o: src/main.c
	gcc -o build/main.o -c src/main.c

clean:
	rm -f build/*.o bin/mnsh
