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

		if(!strcmp(A[0], "list") && n == 1) {
			list(A, n)
			continue;
		}

		if(!strcmp(A[0], "list") && n == 2) {
			DIR * dir;
			struct dirent* entry;

			dir = opendir(A[1]);
			if(dir == NULL) {
				perror("FISH ERROR");
				closedir(dir);
				continue;
			}

			int i = 0;
			while((entry = readdir(dir)) != NULL) {
				printf("%s\n", entry->d_name);
				i++;
			}
			printf("---\n");
			printf("TOTAL: %d items.\n", i);
			closedir(dir);
			continue;
		}

		if(!strcmp(A[0], "list") && n > 2) {
			fprintf(stderr, "FISH SYNTAX ERROR: LIST can only take one or no arguments.\n");
			continue;
		}

		if(!strcmp(A[0], "copy")) {
			if(n != 3) {
				fprintf(stderr, "FISH SYNTAX ERROR: COPY can take only two arguments.\n");
				continue;
			}

			FILE * f1 = fopen(A[1], "r");

			if(f1 == NULL) {
				fprintf(stderr, "FISH: File %s does not exist or cannot be copied.\n", A[1]);
				continue;
			}

			// Allow to copy to a directory
			struct stat st;
			if(lstat(A[2], &st) != -1) {
				if(S_ISDIR(st.st_mode)) {
					int i = strlen(A[2]);
					A[2][i++] = '/';
					int j = 0;

					while(A[1][j] != '\0') { // Concatenate directory, slash, and the name of the file
						A[2][i] = A[1][j];
						i++;
						j++;

						// Doing so, remember about sizes
						if(i == FISH_MAX_WORD_LEN) {	// This is where the infamous GOTO is handy
							fprintf(stderr, "FISH ERROR: File name is too long.\n");
							break;
						}
					}

					// Without GOTO, we have to check the same condition twice. Not a big problem though :)
					if(i == FISH_MAX_WORD_LEN) {
						fprintf(stderr, "FISH ERROR: File name is too long.\n");
						continue;
					}

					A[2][i] = '\0';	// It is still a C-string.
				}
			}


			FILE * f2 = fopen(A[2], "w");

			if(f2 == NULL) {
				fprintf(stderr, "FISH: Cannot copy.\n");
				fclose(f1);
				continue;
			}

			char ch;
			long int i = 0;
			do {
				ch = (char) fgetc(f1);
				if(ch != EOF) {
					fputc((int) ch, f2);
					i++;
				}
			} while(ch != EOF);

			printf("%s ==> %s\n", A[1], A[2]);
			printf("%ld bytes copied.\n", i);

			fclose(f2);
			fclose(f1);

			continue;
		}

		if(!strcmp(A[0], "remove")) {
			if(n != 2) {
				fprintf(stderr, "FISH ERROR: REMOVE command requires one argument.\n");
				continue;
			}

			if(unlink(A[1]) == -1) {
				fprintf(stderr, "FISH ERROR: File %s cannot be removed.\n", A[1]);
			} else {
				fprintf(stderr, "R.I.P., %s\n", A[1]);
			}
			continue;
		}

		if(!strcmp(A[0], "cd")) {
			if(n > 2) {
				fprintf(stderr, "FISH ERROR: REMOVE command requires one or no argument.\n");
				continue;
			}

			if(n == 1) {
				A[1] = getenv("HOME");
			}

			if(chdir(A[1]) == -1) {
				fprintf(stderr, "FISH ERROR: Cannot change directory.\n");
			}

			continue;
		}

		if(!strcmp(A[0], "show")) {
			if(n != 2) {
				fprintf(stderr, "FISH SYNTAX ERROR: SHOW command requires one argument.\n");
				continue;
			}

			
			FILE * f = fopen(A[1], "r");
			
			if(f == NULL) {
				fprintf(stderr, "FISH ERROR: Cannot open file %s\n", A[1]);;
				continue;
			}

			char ch = 0;
			while(ch != EOF) { 
				ch = fgetc(f);
				if(ch != EOF) {
					printf("%c", ch);
				}
			}

			fclose(f);
			
			continue;
		}

		if(!strcmp(A[0], "mkdir")) {
			if(n != 2) {
				fprintf(stderr, "FISH SYNTAX ERROR: MKDIR takes one argument.\n");
				continue;
			}

			if(mkdir(A[1], 0755) == -1) {
				fprintf(stderr, "FISH ERROR: Cannot create a directory.\n");
			} else {
				printf("Welcome on board, %s!\n", A[1]);
			}

			continue;
		}

		if(!strcmp(A[0], "rmdir")) {
			if(n != 2) {
				fprintf(stderr, "FISH SYNTAX ERROR: RMDIR takes one argument.\n");
				continue;
			}

			if(rmdir(A[1]) == -1) {
				fprintf(stderr, "FISH ERROR: Cannot delete a directory.\n");
			} else {
				fprintf(stderr, "R.I.P., %s/\n", A[1]);
			}

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
