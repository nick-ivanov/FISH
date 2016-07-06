# Makefile for fishx

$PROGRAM_NAME = 'fish'

bin/$(PROGRAM_NAME): build/main.o
	g++ -o bin/fish build/main.o

build/main.o: src/main.cpp
	g++ -o build/main.o -c src/main.cpp

clean:
	rm -f build/*.o bin/*
