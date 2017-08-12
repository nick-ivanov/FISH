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

void fish_show(char** A, int n) {
    if(n != 2) {
        fprintf(stderr, "FISH SYNTAX ERROR: SHOW command requires one argument.\n");
        return;
    }

    FILE * f = fopen(A[1], "r");
    
    if(f == NULL) {
        fprintf(stderr, "FISH ERROR: Cannot open file %s\n", A[1]);
        return;
    }

    char ch = 0;
    while(ch != EOF) { 
        ch = fgetc(f);
        if(ch != EOF) {
            printf("%c", ch);
        }
    }

    fclose(f);
}