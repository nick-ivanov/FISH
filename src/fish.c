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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "fish.h"

int main()
{
	int n;
	// Create a dynamic array, and allocate the memory
	char **A = (char **) malloc (FISH_MAX_CMD_WORDS * sizeof(char *));

	if(A == NULL) {
		fprintf(stderr, "System error. Nobody's fault. Try again.\n");
		exit(1);
	}

	int i = 0;
	for(i = 0; i < FISH_MAX_CMD_WORDS; i++) {

		 // Why +1? Because of null-terminators!
		A[i] = (char *) malloc ((FISH_MAX_WORD_LEN+1) * sizeof(char));

		if(A[i] == NULL) {
			fprintf(stderr, "System error. Nobody's fault. Try again.\n");
			exit(1);
		}
	}
	
	while(1) {
		// Command line prompt. Yes, it's a fish!
		printf("[%s] ><(((*> ", getcwd(NULL, 64));

		// Clean the array, just in case
		for(int i = 0; i < FISH_MAX_CMD_WORDS; i++) {
			A[i][0] = '\0';
		} 
		
		n = parse(A);

		if(n == -1) {	// Check the boundaries
			fprintf(stderr, "FISH ERROR: The number of words cannot exceed %d.\n",
						FISH_MAX_CMD_WORDS);	
			continue;
		}

		if(n == -2) {	// Check the boundaries
			fprintf(stderr, "FISH ERROR: A word cannot be longer than %d characters.\n",
					FISH_MAX_WORD_LEN);	
			continue;
		}
		
		// Make commands case insensitve. Arguments remain case-sensitive though.
		tolower_argvx(A, 0);

		if(!strcmp(A[0], "quit")) {
			quit(A, n);
			break;
		}

		if(!strcmp(A[0], "help")) {
			help(A, n);
			continue;
		}

		if(!strcmp(A[0], "run")) {
			run(A, n);
			continue;
		}

		if(!strcmp(A[0], "launch")) {
			launch(A, n);
			continue;
		}

		if(!strcmp(A[0], "list")) {
			list(A, n);
			continue;
		}

		if(!strcmp(A[0], "copy")) {
			copy(A, n);
			continue;
		}

		if(!strcmp(A[0], "remove")) {
			remove(A, n);
			continue;
		}

		if(!strcmp(A[0], "cd")) {
			cd(A, n);
			continue;
		}

		if(!strcmp(A[0], "show")) {
			show(A, n);
			continue;
		}

		if(!strcmp(A[0], "mkdir")) {
			mkdir(A, n);
			continue;
		}

		if(!strcmp(A[0], "rmdir")) {
			rmdir(A, n);
			continue;
		}

		if(A[0][0] == '\0') {
			continue;
		}

		fprintf(stderr, "FISH SYNTAX ERROR: Command '%s' is not implemented. ", A[0]);
		fprintf(stderr, "Ask Nick to implement it.\n");
	}
	
	// Now clean up the mess
	for(int i = 0; i < n; i++) {
		free(A[i]);
	}

	free(A);
	return 0;
}
