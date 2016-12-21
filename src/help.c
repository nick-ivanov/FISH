// TODO: add header

#include <stdio.h>
#include <help.h>

#include "fish.h"

void help(char ** A, int n) {
	if(n > 2) {
				fprintf(stderr, "FISH SYNTAX ERROR: HELP takes one or no arguments.\n");
				return;
			}

			if(n == 1) {
				printf("*** FISH ver. 1.0 -- Fantastically Incredible SHell ***\n\n");
				printf("FISH is a UNIX command interpreter proudly designed\n");
				printf("and implemented at SMSU. Here is the list of commands\n");
				printf("supported by FISH:\n\n");
				printf("RUN, LAUNCH, LIST, COPY, REMOVE, CD, SHOW, HELP, QUIT, MKDIR, RMDIR\n\n");
				printf("To get help on each of those commands, type HELP <command> (i.e. HELP CD)\n");
				printf("NOTE that FISH commands are case-insensitive, yet all the arguments\n");
				printf("are case-sensitive (except for HELP whose argument is case-insensitive).\n\n");
				
				return;
			}

			// Assume n == 2 in here since we are here

			tolower_argvx(A, 1);	// Lowercase the argument

			if(!strcmp(A[1], "run")) {
				printf("RUN executes a program using its filename.\n");
				printf("FORMAT:\n");
				printf("RUN <executable-filename> [<argument1> <argument2> .. <argument9>]\n");
				printf("EXAMPLE:\n");
				printf("\tRUN /bin/ls -l\n");
				return;
			}

			if(!strcmp(A[1], "launch")) {
				printf("LAUNCH searches a program in PATH directories and executes it.\n");
				printf("FORMAT:\n");
				printf("\tLAUNCH <program> [<argument1> <argument2> .. <argument9>]\n");
				printf("EXAMPLE:\n");
				printf("\tLAUNCH ls -l\n");
				return;
			}

			if(!strcmp(A[1], "list")) {
				printf("LIST prints everything that is in a directory.\n");
				printf("With no argument, the contents of the current directory will be shown.\n");
				printf("FORMAT:\n");
				printf("\tLIST [<directory>]\n");
				printf("EXAMPLE:\n");
				printf("\tLIST /\n");
				return;
			}

			if(!strcmp(A[1], "copy")) {
				printf("COPY copies a file. The second argument is either a file or a directory.\n");
				printf("FORMAT:\n");
				printf("\tCOPY <source-file> <destination-file-or-directory>\n");
				printf("EXAMPLE:\n");
				printf("\tCOPY foo.txt bar.txt\n");
				return;
			}

			if(!strcmp(A[1], "remove")) {
				printf("REMOVE deletes a file.\n");
				printf("FORMAT:\n");
				printf("\tREMOVE <file>\n");
				printf("EXAMPLE:\n");
				printf("\tREMOVE foo.txt\n");
				return;
			}

			if(!strcmp(A[1], "cd")) {
				printf("CD changes the current directory.\n");
				printf("With no argument, the home directory will be set as current.\n");
				printf("FORMAT:\n");
				printf("\tCD [<directory>]\n");
				printf("EXAMPLE:\n");
				printf("\tCD /bin\n");
				return;
			}

			if(!strcmp(A[1], "show")) {
				printf("SHOW shows the text contents of a file.\n");
				printf("FORMAT:\n");
				printf("\tSHOW <file>\n");
				printf("EXAMPLE:\n");
				printf("\tSHOW foo.txt\n");
				return;
			}

			if(!strcmp(A[1], "help")) {
				printf("HELP prints documentation on FISH commands and user behavior.\n");
				printf("An optional argument specifies a particular command to get help on.\n");
				printf("FORMAT:\n");
				printf("\tHELP [<fish-command>]\n");
				printf("EXAMPLE:\n");
				printf("\tHELP SHOW\n");
				return;
			}

			if(!strcmp(A[1], "quit")) {
				printf("QUIT exits FISH command interpreter.\n");
				printf("FORMAT:\n");
				printf("\tQUIT\n");
				return;
			}

			if(!strcmp(A[1], "mkdir")) {
				printf("MKDIR creates a new directory.\n");
				printf("FORMAT:\n");
				printf("\tMKDIR <directory-name>\n");
				printf("EXAMPLE:\n");
				printf("\tMKDIR foobar\n");
				return;
			}

			if(!strcmp(A[1], "rmdir")) {
				printf("RMDIR removes an empty directory; if it is not empty, the deletion will fail.\n");
				printf("FORMAT:\n");
				printf("\tRMDIR <directory-name>\n");
				printf("EXAMPLE:\n");
				printf("\tRMDIR foobar\n");
				return;
			}

			fprintf(stderr, "FISH does not have command '%s'\n", A[1]);
			return;
}