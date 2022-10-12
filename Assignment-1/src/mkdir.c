#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int exists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int makeDir(char *dirName, int option_v, int option_p, int showResult) {
    if (exists(dirName) && showResult != 0) {
        printf("mkdir: cannot create directory '%s': File exists \n", dirName);
        return 1;
    }

    if (option_p == 0) {
        if (mkdir(dirName) == -1) {
            if (showResult == 1) {
                printf("mkdir: cannot create directory '%s': No such file or directory \n", dirName);
            }
            return 1;
        }
        if (option_v) {
            printf("mkdir: created directory '%s' \n", dirName);
        }
    }

    else {
        if (mkdir(dirName) != -1) {
            if (option_v) {
                printf("mkdir: created directory '%s' \n", dirName);
            }
            return 0;
        }
        else {
            char *copy = (char *) malloc(256*sizeof(char));
            strcpy(copy, dirName);

            int index = strlen(copy) - 1;
            while (copy[index] != '/') {
                index--;
            }
            copy[index] = '\0';
            makeDir(copy, 0, 1, 0);
            mkdir(dirName);
        }

        if (option_v) {
            printf("mkdir: created directory '%s' \n", dirName);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int *options = (int *) calloc(256, sizeof(int));

    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
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

    if (argc == 1) {
        printf("mkdir: missing operand \n");
        return 1;
    }
    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += makeDir(argv[i], options['v'], options['p'], 1);
        }
    }

    return retSum;
}