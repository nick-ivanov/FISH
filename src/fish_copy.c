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


void fish_copy(char** A, int n) {
    if(n != 3) {
        fprintf(stderr, "FISH SYNTAX ERROR: COPY can take only two arguments.\n");
        return;
    }

    FILE * f1 = fopen(A[1], "r");

    if(f1 == NULL) {
        fprintf(stderr, "FISH: File %s does not exist or cannot be copied.\n", A[1]);
        return;
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
                if(i == FISH_MAX_WORD_LEN) {    // This is where the infamous GOTO is handy
                    fprintf(stderr, "FISH ERROR: File name is too long.\n");
                    break;
                }
            }

            // Without GOTO, we have to check the same condition twice. Not a big problem though :)
            if(i == FISH_MAX_WORD_LEN) {
                fprintf(stderr, "FISH ERROR: File name is too long.\n");
                return;
            }

            A[2][i] = '\0'; // It is still a C-string.
        }
    }

    FILE * f2 = fopen(A[2], "w");

    if(f2 == NULL) {
        fprintf(stderr, "FISH: Cannot copy.\n");
        fclose(f1);
        return;
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
}