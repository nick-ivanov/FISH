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

#include "fish.h"

#include <stdio.h>

int parse(char** A)
{
	char ch;
	int i = 0;
	int n = 0;

	int begin_flag = 1;	// We have not encountered any words yet;

	do {
		//ch = cin.get();
		ch = getchar();

		// Space could be leading, trailing, or between words
		if(ch == ' ') {
			if(!begin_flag) { n++; }	// This space is leading. It is not yet another word.

			if(n >= FISH_MAX_CMD_WORDS) { // Too many words
				n = -1;		// Save error status
				do { ch = getchar(); } while (ch != '\n'); // Flush drop by drop
				return n;		// Get out of here completely
			}

			do {	// Skip a series of spaces
				ch = getchar();
				if(ch == '\n') { return n; }	// It was a trailing space
			} while (ch == ' ');	// Is it still a space?

			i = 0;	// New word
		}

		if(ch == '\n') {	// End of input
			if(begin_flag) { n = 0; return n; }	// The empty line case
			break;	// Nothing else to do
		}

		begin_flag = 0;// So we are no longer reading a series of leading spaces

		if(i >= FISH_MAX_WORD_LEN) { // One of the words is too long
			n = -2;	// Save error status
			do { ch = getchar(); } while (ch != '\n'); // Flush drop by drop
			return n;	// Get out of here completely
		}
		
		A[n][i++] = ch;	// Write character, increment counter
		A[n][i] = '\0';	// Terminate each time. Who said it is the fastest shell in the world?
	} while (1);	// Sentinnel control should occur in the middle of the loop

	// Now if the line has some words, transform the index of last word into the array size
	if(!begin_flag) { n++; }

	return n;
}
