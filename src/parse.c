#include "parse.h"

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
