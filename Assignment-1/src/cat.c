#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        void *end = fgets(input, maxSize, stdin);
        while (end != EOF) {
            puts(input);
            end = fgets(input, maxSize, stdin);
        }

        return 0;
    }

    return 0;
}
// -n -E