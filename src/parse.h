/*
FILE NAME:     fish.c
VERSION:       1.1
DESCRIPTION:   Fantasticly Incredible Shell (FISH) -- pretty good Unux shell.
AUTHOR:        Copyright (C) 2015-2016 Nikolay Ivanov (Nick) <nnrowan@gmail.com>
LICENSE:       GNU General Public License v.3
               [http://www.gnu.org/licenses/gpl-3.0.en.html]

DOCUMENTATION: Build and run the program; then type HELP to
                     to see the list of commands:
                     $ make
                     $ ./fish
                     [...] ><(((*> HELP
*/

/* 
This function reads a line from the keyboard and writes each
word into an array of strings. The array and its resulting size
are passed as arguments by reference. The function checks the
boundaries and ignores any series of spaces wherever they are.

NOTE: This version of the function is not designed to process
tabs and other whitespace characters.

ARGUMENTS:
	A:		array of strings the words will be written into;

RETURN VALUE: The number of words read.
*/

int parse(char** A);