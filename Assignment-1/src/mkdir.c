#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int exists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int makeDir(char *dirName, int option_v, int option_p) {
    char *token = strtok(dirName, "/");

    if (option_p == 0 && exists(dirName)) {
        printf("mkdir: cannot create directory '%s': File exists \n");
        return 1;
    }
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
            if (option != 'v' && option != 'p') {
                printf("mkdir: invalid option -- '%c' \n", option);
                return 1;
            }
            options[option]++;
        }
    }

    if (args == 0) {
        printf("mkdir: missing operand \n");
        return 1;
    }

    int retSum = 0;
    for (int i=1; i < args; i++) {
        if (argv[i][0] != '-') {
            retSum += makeDir(argv[i], options['v'], options['p']);
        }
    }

    return retSum;
}