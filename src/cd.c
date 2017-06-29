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

void cd(char** A, int n) {
    if(n > 2) {
        fprintf(stderr, "FISH ERROR: REMOVE command requires one or no argument.\n");
        return;
    }

    if(n == 1) {
        A[1] = getenv("HOME");
    }

    if(chdir(A[1]) == -1) {
        fprintf(stderr, "FISH ERROR: Cannot change directory.\n");
    }
}