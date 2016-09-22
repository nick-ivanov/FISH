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
void parse(char** A, int& n)
{
	char ch;
	int i = 0;
	n = 0;

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
				return;		// Get out of here completely
			}

			do {	// Skip a series of spaces
				ch = getchar();
				if(ch == '\n') { return; }	// It was a trailing space
			} while (ch == ' ');	// Is it still a space?

			i = 0;	// New word
		}

		if(ch == '\n') {	// End of input
			if(begin_flag) { n = 0; return; }	// The empty line case
			break;	// Nothing else to do
		}

		begin_flag = 0;// So we are no longer reading a series of leading spaces

		if(i >= FISH_MAX_WORD_LEN) { // One of the words is too long
			n = -2;	// Save error status
			do { ch = getchar(); } while (ch != '\n'); // Flush drop by drop
			return;	// Get out of here completely
		}
		
		A[n][i++] = ch;	// Write character, increment counter
		A[n][i] = '\0';	// Terminate each time. Who said it is the fastest shell in the world?
	} while (1);	// Sentinnel control should occur in the middle of the loop

	// Now if the line has some words, transform the index of last word into the array size
	if(!begin_flag) { n++; }
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
	
	while(true) {
		// Command line prompt. Yes, it's a fish!
		printf("[%s] ><(((*> ", getcwd(NULL, 64));

		// Clean the array, just in case
		for(int i = 0; i < FISH_MAX_CMD_WORDS; i++) {
			A[i][0] = '\0';
		} 
		
		n = 0;
		parse(A, n); // TODO: Fix pass by reference

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
				cout << "EXAMPLE:" << endl;
				cout << "\tRUN /bin/ls -l" << endl;
				continue;
			}

			if(!strcmp(A[1], "launch")) {
				cout << "LAUNCH searches a program in PATH directories and executes it." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tLAUNCH <program> [<argument1> <argument2> .. <argument9>]" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tLAUNCH ls -l" << endl;
				continue;
			}

			if(!strcmp(A[1], "list")) {
				cout << "LIST prints everything that is in a directory." << endl;
				cout << "With no argument, the contents of the current directory will be shown." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tLIST [<directory>]" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tLIST /" << endl;
				continue;
			}

			if(!strcmp(A[1], "copy")) {
				cout << "COPY copies a file. The second argument is either a file or a directory." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tCOPY <source-file> <destination-file-or-directory>" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tCOPY foo.txt bar.txt" << endl;
				continue;
			}

			if(!strcmp(A[1], "remove")) {
				cout << "REMOVE deletes a file." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tREMOVE <file>" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tREMOVE foo.txt" << endl;
				continue;
			}

			if(!strcmp(A[1], "cd")) {
				cout << "CD changes the current directory." << endl;
				cout << "With no argument, the home directory will be set as current." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tCD [<directory>]" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tCD /bin" << endl;
				continue;
			}

			if(!strcmp(A[1], "show")) {
				cout << "SHOW shows the text contents of a file." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tSHOW <file>" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tSHOW foo.txt" << endl;
				continue;
			}

			if(!strcmp(A[1], "help")) {
				cout << "HELP prints documentation on FISH commands and user behavior." << endl;
				cout << "An optional argument specifies a particular command to get help on." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tHELP [<fish-command>]" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tHELP SHOW" << endl;
				continue;
			}

			if(!strcmp(A[1], "quit")) {
				cout << "QUIT exits FISH command interpreter." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tQUIT" << endl;
				continue;
			}

			if(!strcmp(A[1], "mkdir")) {
				cout << "MKDIR creates a new directory." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tMKDIR <directory-name>" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tMKDIR foobar" << endl;
				continue;
			}

			if(!strcmp(A[1], "rmdir")) {
				cout << "RMDIR removes an empty directory; if it is not empty, the deletion will fail." << endl;
				cout << "FORMAT:" << endl;
				cout << "\tRMDIR <directory-name>" << endl;
				cout << "EXAMPLE:" << endl;
				cout << "\tRMDIR foobar" << endl;
				continue;
			}

			cerr << "FISH does not have command '" << A[1] << "'" << endl;
			continue;
		}

		if(!strcmp(A[0], "run")) {
			if(n < 2 || n > 10) {
				cerr << "FISH SYNTAX ERROR: Command RUN takes one to nine arguments." << endl;
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
						cerr << "FISH SYNTAX ERROR: Command RUN takes one to eleven arguments." << endl;
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
				cerr << "FISH SYNTAX ERROR: Command LAUNCH takes one to nine arguments." << endl;
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
						cerr << "FISH SYNTAX ERROR: Command LAUNCH takes one to eleven arguments." << endl;
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
				cout << entry->d_name << endl;
				i++;
			}
			cout << "---" << endl;
			cout << "TOTAL: " << i << " items." << endl;
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
				cout << entry->d_name << endl;
				i++;
			}
			cout << "---" << endl;
			cout << "TOTAL: " << i << " items." << endl;
			closedir(dir);
			continue;
		}

		if(!strcmp(A[0], "list") && n > 2) {
			cerr << "FISH SYNTAX ERROR: LIST can only take one or no arguments." << endl;
			continue;
		}

		if(!strcmp(A[0], "copy")) {
			if(n != 3) {
				cerr << "FISH SYNTAX ERROR: COPY can take only two arguments." << endl;
				continue;
			}

//			ifstream f1(A[1]);
//			if(!f1) {
//				cerr << "FISH: File " << f1 << " does not exist or cannot be copied." << endl;
//				continue;
//			}

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
							cerr << "FISH ERROR: File name is too long." << endl;
							break;
						}
					}

					// Without GOTO, we have to check the same condition twice. Not a big problem though :)
					if(i == FISH_MAX_WORD_LEN) {
						cerr << "FISH ERROR: File name is too long." << endl;
						continue;
					}

					A[2][i] = '\0';	// It is still a C-string.
				}
			}

//			ofstream f2(A[2]);
//			if(!f2) {
//				cerr << "FISH: Cannot copy." << endl;
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

			cout << A[1] << " ==> " << A[2] << endl;
			cout << i << " bytes copied." << endl;

			f2.close();
			f1.close();

*/
			continue;
		}

		if(!strcmp(A[0], "remove")) {
			if(n != 2) {
				cerr << "FISH ERROR: REMOVE command requires one argument." << endl;
				continue;
			}

			if(unlink(A[1]) == -1) {
				cerr << "FISH ERROR: File " << A[1] << " cannot be removed." << endl;
			} else {
				cerr << "R.I.P., " << A[1] << endl;
			}
			continue;
		}

		if(!strcmp(A[0], "cd")) {
			if(n > 2) {
				cerr << "FISH ERROR: REMOVE command requires one or no argument." << endl;
				continue;
			}

			if(n == 1) {
				A[1] = getenv("HOME");
			}

			if(chdir(A[1]) == -1) {
				cerr << "FISH ERROR: Cannot change directory." << endl;
			}

			continue;
		}

		if(!strcmp(A[0], "show")) {
			if(n != 2) {
				cerr << "FISH SYNTAX ERROR: SHOW command requires one argument." << endl;
				continue;
			}

			ifstream f(A[1]);
			if(!f) {
				cerr << "FISH ERROR: Cannot open file " << A[1] << endl;
				continue;
			}

			char ch;
			while(!f.eof()) { 
				ch = f.get();
				if(ch != EOF) { cout << ch; }
			}

			f.close();
			continue;
		}

		if(!strcmp(A[0], "mkdir")) {
			if(n != 2) {
				cerr << "FISH SYNTAX ERROR: MKDIR takes one argument." << endl;
				continue;
			}

			if(mkdir(A[1], 0755) == -1) {
				cerr << "FISH ERROR: Cannot create a directory." << endl;
			} else {
				cout << "Welcome on board, " << A[1] << "!" << endl;
			}

			continue;
		}

		if(!strcmp(A[0], "rmdir")) {
			if(n != 2) {
				cerr << "FISH SYNTAX ERROR: RMDIR takes one argument." << endl;
				continue;
			}

			if(rmdir(A[1]) == -1) {
				cerr << "FISH ERROR: Cannot delete a directory." << endl;
			} else {
				cerr << "R.I.P., " << A[1] << "/" << endl;
			}

			continue;
		}

		if(A[0][0] == '\0') { continue; }

		cerr << "FISH SYNTAX ERROR: Command '" << A[0] << "' is not implemented. ";
		cerr << "Ask Nick to implement it." << endl;
	}
	
	// Now clean up the mess
	for(int i = 0; i < n; i++) {
		delete [] A[i];
	}

	delete [] A;
	return 0;
}