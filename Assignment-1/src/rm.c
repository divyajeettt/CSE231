#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int fileExists(char *fName) {
    return (access(fName, F_OK) == 0);
}


int dirExists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int rm(char *name, int option_r, int option_v, int showResult) {
    if (!(fileExists(name) || dirExists(name))) {
        printf("rm: cannot remove '%s': No such file or directory \n", name);
        return 1;
    }

    if (option_r == 0) {
        if (dirExists(name)) {
            printf("rm: cannot remove '%s': Is a directory \n", name);
            return 1;
        }
        if (remove(name) != 0) {
            if (showResult == 1) {
                printf("rm: cannot remove directory '%s': No such file or directory \n", name);
            }
            return 1;
        }
        if (option_v) {
            printf("removed '%s' \n", name);
        }
    }

    else {
        if (remove(name) == 0) {
            if (option_v) {
                printf("removed '%s' \n", name);
            }
            return 1;
        }
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
            if (option != 'r' && option != 'R' && option != 'v') {
                printf("rm: invalid option -- '%c' \n", option);
                return 1;
            }
            options[option]++;
        }

        if (args == 0) {
            printf("rm: missing operand \n");
            return 1;
        }
    }

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += rm(argv[i], options['r']+options['R'], options['v'], 1);
        }
    }

    return retSum;
}