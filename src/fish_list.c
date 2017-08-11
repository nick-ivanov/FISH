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

void list(char** A, int n) {
    if(n == 1) {
        DIR * dir;
        struct dirent* entry;

        dir = opendir(getcwd(NULL, 256));

        if(dir == NULL) {
            perror("FISH ERROR");
            closedir(dir);
            return;
        }

        int i = 0;
        while((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
            i++;
        }

        printf("---\n");
        printf("TOTAL: %d items.\n", i);
        closedir(dir);
    } else if(n == 2) {
        DIR * dir;
        struct dirent* entry;

        dir = opendir(A[1]);
        if(dir == NULL) {
            perror("FISH ERROR");
            closedir(dir);
            return;
        }

        int i = 0;
        while((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
            i++;
        }
        printf("---\n");
        printf("TOTAL: %d items.\n", i);
        closedir(dir);
    } else {
        fprintf(stderr, "FISH SYNTAX ERROR: LIST can only take one or no arguments.\n");
    }
}