#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_SIZE 256

///////////////////////////////////////////////////////////////////////////////////////////////////

int exists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int makeDir(char *dirName, int option_v, int option_p, int showResult) {
    if (exists(dirName) && option_p == 0 && showResult != 0) {
        printf("mkdir: cannot create directory '%s': File exists \n", dirName);
        return 1;
    }

    if (option_p == 0) {
        if (mkdir(dirName, S_IRWXU) == -1) {
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
        if (mkdir(dirName, S_IRWXU) != 0) {
            char *copy = (char *) malloc(MAX_SIZE*sizeof(char));
            strcpy(copy, dirName);

            int index = strlen(copy) - 1;
            while (copy[index] != '/') {
                index--;
            }
            copy[index] = '\0';

            makeDir(copy, option_v, 1, 0);
            mkdir(dirName, S_IRWXU);
        }

        if (option_v) {
            printf("mkdir: created directory '%s' \n", dirName);
        }
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
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += makeDir(argv[i], options['v'], options['p'], 1);
        }
    }

    return retSum;
}