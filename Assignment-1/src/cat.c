#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_SIZE 256

///////////////////////////////////////////////////////////////////////////////////////////////////

int exists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int cat(char *filename, int option_n, int option_E, int *counter) {
    FILE *file;
    if (strcmp(filename, "stdin") == 0) {
        file = stdin;
    }
    else {
        if (exists(filename)) {
            printf("cat: %s: Is a directory \n", filename);
            return 1;
        }
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("cat: %s: No such file or directory \n", filename);
            return 1;
        }
    }

    int read;
    char *line = (char *) malloc(MAX_SIZE*sizeof(char));

    size_t size;
    while ((read = getline(&line, &size, file)) != -1) {
        if (option_n > 0) {
            printf("%6d  ", (*counter)++);
        }

        line[read-1] = ((line[read-1] == '\n') ? '\0' : line[read-1]);
        printf("%s", line);

        if (option_E > 0) {
            printf("$");
        }

        printf("\n");
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int *options = (int *) calloc(MAX_SIZE, sizeof(int));
    int args = 0;

    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            args++;
            continue;
        }
        for (int j=1; j < strlen(argv[i]); j++) {
            char option = argv[i][j];
            if (option != 'n' && option != 'E') {
                printf("cat: invalid option -- '%c' \n", option);
                return 1;
            }
            options[option]++;
        }
    }

    int counter = 1;

    if (args == 0) {
        return cat("stdin", options['n'], options['E'], &counter);
    }

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += cat(argv[i], options['n'], options['E'], &counter);
        }
    }

    return retSum;
}