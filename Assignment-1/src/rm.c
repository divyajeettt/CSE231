#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int fileExists(char *fName) {
    return (access(fName, F_OK) == 0);
}


int dirExists(char *dirName) {
    return (opendir(dirName) != NULL);
}


int rm(char *name, int option_v, int option_r, int showResult) {
    char *cwd = (char *) malloc(256*sizeof(char));
    getcwd(cwd, 256);
    printf("cwd=%s \n", cwd);

    if (!(fileExists(name) || dirExists(name))) {
        printf("1. rm: cannot remove '%s': No such file or directory \n", name);
        return 1;
    }

    if (option_r == 0) {
        if (dirExists(name)) {
            printf("rm: cannot remove '%s': Is a directory \n", name);
            return 1;
        }
        if (remove(name) != 0) {
            if (showResult == 1) {
                printf("2. rm: cannot remove directory '%s': No such file or directory \n", name);
            }
            return 1;
        }
        if (option_v) {
            printf("removed '%s' \n", name);
        }
    }

    else {
        if (remove(name) != 0 && dirExists(name)) {
            DIR *dirHandler = opendir(name);
            struct dirent *dir;

            while ((dir = readdir(dirHandler)) != NULL) {
                printf("%s \n", dir->d_name);
                if (fileExists(dir->d_name)) {
                    remove(dir->d_name);
                }
                else {
                    rm(realpath(dir->d_name, NULL), 0, 1, 0);
                }
            }
        }

        if (option_v) {
            printf("removed '%s' \n", name);
        }
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

// int main(int argc, char *argv[]) {
int main() {
    int *options = (int *) calloc(256, sizeof(int));
    int args = 0;

    int argc = 3;
    char *argv[] = {"rm", "crimge", "-r"};

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
            retSum += rm(argv[i], options['v'], options['r']+options['R'], 1);
        }
    }

    return retSum;
}