// TODO: add header

#include <stdio.h>
#include <string.h>

#include "fish.h"

void run(char ** A, int n) {
	if(n < 2 || n > 10) {
		fprintf(stderr, "FISH SYNTAX ERROR: Command RUN takes one to nine arguments.\n");
		return;
	}

	pid_t pid = fork();

	if(pid == -1) {
		perror("FISH internal error.");
		return;
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
				return;
		}

		perror("FISH ERROR");
		exit(1);	// The child is still alive and kickin'.
	} else {
		wait(NULL);
	}
}