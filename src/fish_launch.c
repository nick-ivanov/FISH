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

#include <stdio.h>
#include <unistd.h>

#include "fish.h"

void fish_launch(char** A, int n) {
    if(n < 2 || n > 10) {
                fprintf(stderr, "FISH SYNTAX ERROR: Command LAUNCH takes one to nine arguments.\n");
                return;
            }

            pid_t pid = fork();

            if(pid == -1) {
                perror("FISH internal error.");
                return;
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
                        return;
                }

                perror("FISH ERROR");
                exit(1);    // The child is still alive and kickin'.
            } else {
                wait(NULL);
            }
}