/*
FILE NAME:     parse.h
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


#define FISH_MAX_CMD_WORDS	64		// Maximum number of words in a command
#define FISH_MAX_WORD_LEN	256		// Maximum length of a word


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



/*
This function converts capital letter in ARGV[index] into lower case.
This function is used for support of case-insensitive commands, as well
as case-insensitive arguments of HELP command.

ARGUMENTS:
	ARGV:			array of C-strings;
	index:			the index of the string to process.
RETURN VALUE: None
*/

void tolower_argvx(char** ARGV, int index);


/* TODO: Function description */
void help(int n);