/*
    Fantasticly Incredible Shell (FISH) -- a pretty good Unux shell
    Copyright (C) 2015-2017  Nick Ivanov <nnrowan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
void fish_tolower_argvx(char** ARGV, int index);

/* TODO: Function description */
int fish_parse(char** A, int n);

/* TODO: Function description */
void fish_help(char** A, int n);


/* TODO: Function description */
void fish_run(char** A, int n);

/* TODO: Function description */
void fish_quit(char** A, int n);


/* TODO: Function description */
void fish_launch(char** A, int n);

/* TODO: Function description */
void fish_list(char** A, int n);

/* TODO: Function description */
void fish_copy(char** A, int n);

/* TODO: Function description */
void fish_remove(char** A, int n);

/* TODO: Function description */
void fish_cd(char** A, int n);

/* TODO: Function description */
void fish_show(char** A, int n);

/* TODO: Function description */
void fish_mkdir(char** A, int n);

/* TODO: Function description */
void fish_rmdir(char** A, int n);



