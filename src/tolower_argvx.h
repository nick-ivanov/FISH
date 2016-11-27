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

#include <ctype.h>

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