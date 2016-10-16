/*
FILE NAME:     fish.c
VERSION:       1.0
DESCRIPTION:   Fantasticly Incredible Shell (FISH) -- pretty good Unux shell.
AUTHOR:        Nikolay Ivanov (Nick) <nnrowan@gmail.com>
LICENSE:       GNU General Public License v.3
               [http://www.gnu.org/licenses/gpl-3.0.en.html]
DATE:          12/09/2015

DOCUMENTATION: Build and run the program; then type HELP to
                     to see the list of commands:
                     $ gcc -o fish fish.c
                     $ ./fish
                     ><(((*> HELP
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

#define FISH_MAX_CMD_WORDS	64		// Maximum number of words in a command
#define FISH_MAX_WORD_LEN	256		// Maximum length of a word


/* This function converts capital letter in ARGV[index] into lower case.
This function is used for support of case-insensitive commands, as well
as case-insensitive arguments of HELP command.

ARGUMENTS:
	ARGV:			array of C-strings;
	index:			the index of the string to process.
RETURN VALUE: None */
void tolower_argvx(char** ARGV, int index)
{
	int i = 0;
	while(ARGV[index][i] != '\0') { ARGV[index][i] = tolower(ARGV[index][i]); i++; }
}

/* This function reads a line from the keyboard and writes each
word into an array of strings. The array and its resulting size
are passed as arguments by reference. The function checks the
boundaries and ignores any series of spaces wherever they are.

NOTE: This version of the function is not designed to process
tabs and other whitespace characters.

ARGUMENTS:
	A:		array of strings the words will be written into;
	n:		passed by reference, obtains the number of words read. 
RETURN VALUE: None */
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

/* The show starts in here */
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
			fprintf(stderr, "System error. Nobody's fault. Try again.");
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
			if(n > 1) {
				fprintf(stderr, "FISH SYNTAX ERROR: QUIT does not take any arguments.\n");
				continue;
			}

			printf("Thank you for using Fantastically Incredible Shell (FISH)!\n");
			printf("Glub-glub!\n");
			break;
		}

		if(!strcmp(A[0], "help")) {
			if(n > 2) {
				fprintf(stderr, "FISH SYNTAX ERROR: HELP takes one or no arguments.\n");
				continue;
			}

			if(n == 1) {
				printf("*** FISH ver. 1.0 -- Fantastically Incredible SHell ***\n\n");
				printf("FISH is a UNIX command interpreter proudly designed\n");
				printf("and implemented at SMSU. Here is the list of commands\n");
				printf("supported by FISH:\n\n");
				printf("RUN, LAUNCH, LIST, COPY, REMOVE, CD, SHOW, HELP, QUIT, MKDIR, RMDIR\n\n");
				printf("To get help on each of those commands, type HELP <command> (i.e. HELP CD)");
				printf("NOTE that FISH commands are case-insensitive, yet all the arguments\n");
				printf("are case-sensitive (except for HELP whose argument is case-insensitive).\n");
				
				continue;
			}

			// Assume n == 2 in here since we are here

			tolower_argvx(A, 1);	// Lowercase the argument

			if(!strcmp(A[1], "run")) {
				printf("RUN executes a program using its filename.\n");
				printf("FORMAT:\n");
				printf("RUN <executable-filename> [<argument1> <argument2> .. <argument9>]\n");
				printf("EXAMPLE:\n");
				printf("\tRUN /bin/ls -l\n");
				continue;
			}

			if(!strcmp(A[1], "launch")) {
				printf("LAUNCH searches a program in PATH directories and executes it.\n");
				printf("FORMAT:\n");
				printf("\tLAUNCH <program> [<argument1> <argument2> .. <argument9>]\n");
				printf("EXAMPLE:\n");
				printf("\tLAUNCH ls -l\n");
				continue;
			}

			if(!strcmp(A[1], "list")) {
				printf("LIST prints everything that is in a directory.\n");
				printf("With no argument, the contents of the current directory will be shown.\n");
				printf("FORMAT:\n");
				printf("\tLIST [<directory>]\n");
				printf("EXAMPLE:\n");
				printf("\tLIST /\n");
				continue;
			}

			if(!strcmp(A[1], "copy")) {
				printf("COPY copies a file. The second argument is either a file or a directory.\n");
				printf("FORMAT:\n");
				printf("\tCOPY <source-file> <destination-file-or-directory>\n");
				printf("EXAMPLE:\n");
				printf("\tCOPY foo.txt bar.txt\n");
				continue;
			}

			if(!strcmp(A[1], "remove")) {
				printf("REMOVE deletes a file.\n");
				printf("FORMAT:\n");
				printf("\tREMOVE <file>\n");
				printf("EXAMPLE:\n");
				printf("\tREMOVE foo.txt\n");
				continue;
			}

			if(!strcmp(A[1], "cd")) {
				printf("CD changes the current directory.\n");
				printf("With no argument, the home directory will be set as current.\n");
				printf("FORMAT:\n");
				printf("\tCD [<directory>]\n");
				printf("EXAMPLE:\n");
				printf("\tCD /bin\n");
				continue;
			}

			if(!strcmp(A[1], "show")) {
				printf("SHOW shows the text contents of a file.\n");
				printf("FORMAT:\n");
				printf("\tSHOW <file>\n");
				printf("EXAMPLE:\n");
				printf("\tSHOW foo.txt\n");
				continue;
			}

			if(!strcmp(A[1], "help")) {
				printf("HELP prints documentation on FISH commands and user behavior.\n");
				printf("An optional argument specifies a particular command to get help on.\n");
				printf("FORMAT:\n");
				printf("\tHELP [<fish-command>]\n");
				printf("EXAMPLE:\n");
				printf("\tHELP SHOW\n");
				continue;
			}

			if(!strcmp(A[1], "quit")) {
				printf("QUIT exits FISH command interpreter.\n");
				printf("FORMAT:\n");
				printf("\tQUIT\n");
				continue;
			}

			if(!strcmp(A[1], "mkdir")) {
				printf("MKDIR creates a new directory.\n");
				printf("FORMAT:\n");
				printf("\tMKDIR <directory-name>\n");
				printf("EXAMPLE:\n");
				printf("\tMKDIR foobar\n");
				continue;
			}

			if(!strcmp(A[1], "rmdir")) {
				printf("RMDIR removes an empty directory; if it is not empty, the deletion will fail.\n");
				printf("FORMAT:\n");
				printf("\tRMDIR <directory-name>\n");
				printf("EXAMPLE:\n");
				printf("\tRMDIR foobar\n");
				continue;
			}

			fprintf(stderr, "FISH does not have command '%s'\n", A[1]);
			continue;
		}

		if(!strcmp(A[0], "run")) {
			if(n < 2 || n > 10) {
				fprintf(stderr, "FISH SYNTAX ERROR: Command RUN takes one to nine arguments.\n");
				continue;
			}

			pid_t pid = fork();

			if(pid == -1) {
				perror("FISH internal error.");
				continue;
			} else if (pid == 0) {
				switch(n) // Yes it looks gloomy, but it is easier than using execv()!
				{
					case 2: execl(A[1], A[1], NULL); break;
					case 3: execl(A[1], A[1], A[2], NULL); break;
					case 4: execl(A[1], A[1], A[2], A[3], NULL); break;
					case 5: execl(A[1], A[1], A[2], A[3], A[4], NULL); break;
					case 6: execl(A[1], A[1], A[2], A[3], A[4], A[5], NULL); break;
					case 7: execl(A[1], A[1], A[2], A[3], A[4], A[5], A[6], NULL); break;
					case 8: execl(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], NULL); break;
					case 9: execl(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[5], NULL); break;
					case 10: execl(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[8], A[9], NULL); break;
					
					default:
						fprintf(stderr, "FISH SYNTAX ERROR: Command RUN takes one to eleven arguments.\n");
						continue;
				}

				perror("FISH ERROR");
				exit(1);	// The child is still alive and kickin'.
			} else {
				wait(NULL);
			}

			continue;
		}

		if(!strcmp(A[0], "launch")) {
			if(n < 2 || n > 10) {
				fprintf(stderr, "FISH SYNTAX ERROR: Command LAUNCH takes one to nine arguments.\n");
				continue;
			}

			pid_t pid = fork();

			if(pid == -1) {
				perror("FISH internal error.");
				continue;
			} else if (pid == 0) {
				switch(n) // Yes it looks gloomy, but it is easier than using execvp()!
				{
					case 2: execlp(A[1], A[1], NULL); break;
					case 3: execlp(A[1], A[1], A[2], NULL); break;
					case 4: execlp(A[1], A[1], A[2], A[3], NULL); break;
					case 5: execlp(A[1], A[1], A[2], A[3], A[4], NULL); break;
					case 6: execlp(A[1], A[1], A[2], A[3], A[4], A[5], NULL); break;
					case 7: execlp(A[1], A[1], A[2], A[3], A[4], A[5], A[6], NULL); break;
					case 8: execlp(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], NULL); break;
					case 9: execlp(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[5], NULL); break;
					case 10: execlp(A[1], A[1], A[2], A[3], A[4], A[5], A[6], A[7], A[8], A[9], NULL); break;
					
					default:
						fprintf(stderr, "FISH SYNTAX ERROR: Command LAUNCH takes one to eleven arguments.\n");
						continue;
				}

				perror("FISH ERROR");
				exit(1);	// The child is still alive and kickin'.
			} else {
				wait(NULL);
			}

			continue;
		}

		if(!strcmp(A[0], "list") && n == 1) {
			DIR * dir;
			struct dirent* entry;

			dir = opendir(getcwd(NULL, 256));

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
				fprintf(stderr, "FISH: File " << f1 << " does not exist or cannot be copied.\n");
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

//			ofstream f2(A[2]);
//			if(!f2) {
//				fprintf(stderr, "FISH: Cannot copy.\n");
//				f1.close();
//				continue;
//			}
/*
			char ch;
			long int i = 0;
			do {
				ch = f1.get();
				if(ch != EOF) {
					f2.put(ch);
					i++;
				}
			} while(!f1.eof());

			printf(A[1] << " ==> " << A[2] << endl;
			printf(i << " bytes copied.\n");

			f2.close();
			f1.close();

*/
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

/*			ifstream f(A[1]);
			if(!f) {
				fprintf(stderr, "FISH ERROR: Cannot open file %s\n", A[1]);;
				continue;
			}

			char ch;
			while(!f.eof()) { 
				ch = f.get();
				if(ch != EOF) { printf(ch); }
			}

			f.close();
			*/
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
