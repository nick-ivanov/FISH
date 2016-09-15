/*
    mnsh -- Minnesota Shell: command interpreter for Linux
    Copyright (C) 2015-2016  Nick Ivanov <nick@nnbits.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define NN_TRUE 1
#define NN_FALSE 0
#define MAX_COMMAND_LENGTH 4096

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	printf("Welcome to Minnesota Shell (mnsh)!\n");

	short int status_repeat = NN_TRUE;
	char user_input[4096];

	while(status_repeat) {
		printf("mnsh> ");
		scanf("%s", &user_input);
		user_input[MAX_COMMAND_LENGTH] = '\0';

		if(!strncmp(user_input, "quit", 4)) {
			printf("Thank you for using Minnesota Shell!\n");
			break;
		}

		printf("Reply: %s\n", user_input);
	}

	return(EXIT_SUCCESS);
}
