#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int cat(char *filename, int option_n, int option_E) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("cat: %s: No such file or directory \n", filename);
        return 1;
    }

    int read;
    int counter = 1;
    size_t maxSize = 256;
    char *line = (char *) malloc(maxSize*sizeof(char));

    while ((read = getline(&line, &maxSize, file)) != -1) {
        if (option_n > 0) {
            printf("%-5d  ", counter++);
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
        int maxSize = 256;
        char *input = (char *) malloc(maxSize*sizeof(char));

        char *end = fgets(input, maxSize, stdin);
        while (end != NULL) {
            int length = strlen(input) - 1;
            if (input[length] == '\n') {
                input[length] = '\0';
            }
            puts(input);
            end = fgets(input, maxSize, stdin);
        }

        return 0;
    }

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += cat(argv[i], options['n'], options['E']);
        }
    }

    return 0;
}