#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int exists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int cat(char *filename, int option_n, int option_E) {
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
    int counter = 1;
    size_t maxSize = 256;
    char *line = (char *) malloc(maxSize*sizeof(char));

    while ((read = getline(&line, &maxSize, file)) != -1) {
        if (option_n > 0) {
            printf("%6d  ", counter++);
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
    int *options = (int *) calloc(256, sizeof(int));
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

    if (args == 0) {
        return cat("stdin", options['n'], options['E']);
    }

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += cat(argv[i], options['n'], options['E']);
        }
    }

    return retSum;
}