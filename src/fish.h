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



/****************************************************************************
PURPOSE: Convert capital letters in ARGV[index] into lowercase.

ARGUMENTS:
	- ARGV: array of C-strings;
	- index: position (index) of the string in ARGV to convert to lowercase.

RETURN VALUE: None
*/
void fish_tolower_argvx(char** ARGV, int index);
/***************************************************************************/




/****************************************************************************
PURPOSE: Read user command from standard input, split it into words, and
	put the result into the array A.

ARGUMENTS:
	- A: array of C-strings (two-dimentional array of chars) where the
		result will be written into.

RETURN VALUE: The number of strings put in A.
*/
int fish_readcommand(char** A);
/***************************************************************************/




/****************************************************************************
PURPOSE: Print general FISH help message or a specific command help message.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_help(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Run an executable using a direct path to its executable file.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_run(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Quit FISH with return code 0.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_quit(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Execute a program by searching its executable in the PATH-listed
	directories.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_launch(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: List the contents of the current directory or the directory
	specified by the argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_list(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Copy the file specified in the first argument into the file
	specified by the second argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_copy(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Remove the file specified by the argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_remove(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Change current directory into the one specified by the argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_cd(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Show the contents of the file specified by the argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_show(char** A, int n);
/***************************************************************************/




/****************************************************************************
PURPOSE: Create a directory specified by the argument.

ARGUMENTS:
	- A: array of C-strings containing FISH command and its arguments;
	- n: number of words in array A.

RETURN VALUE: None
*/
void fish_mkdir(char** A, int n);
/***************************************************************************/




/* TODO: Function description */
void fish_rmdir(char** A, int n);



