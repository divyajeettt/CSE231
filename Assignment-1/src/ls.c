#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int ls(char *dirName, int option_a, int option_1) {
    if (dirName == NULL) {
        dirName = (char *) malloc(256*sizeof(char));
        getcwd(dirName, 256);
    }

    DIR *dirHandler = opendir(dirName);

    if (dirHandler == NULL) {
        if (errno = ENOENT) {
            printf("ls: cannot access '%s': No such file or directory \n", dirName);
		}
        return 1;
	}

    struct dirent *dir;
    while ((dir = readdir(dirHandler)) != NULL) {
        if (option_a == 0 && dir->d_name[0] == '.') {
			continue;
        }
        printf("%s  ", dir->d_name);
        if (option_1 > 0) {
            printf("\n");
        }
    }

    if (option_1 == 0) {
        printf("\n");
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int *options = (int *) calloc(256, sizeof(int));
    int args = 0;

    for (int i=0; i < argc; i++) {
        if (argv[i][0] != '-') {
            args++;
            continue;
        }
        for (int j=1; j < strlen(argv[i]); j++) {
            char option = argv[i][j];
            if (option != 'a' && option != '1') {
                printf("ls: invalid option -- '%c' \n", option);
                return 1;
            }
            options[option]++;
        }
    }

    if (args == 1) {
        return ls(NULL, options['a'], options['1']);
    }

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-' && strmp(argv[i], "") != 0) {
            if (args > 1) {
                printf("%s: \n", argv[i]);
            }
            retSum += ls(argv[i], options['a'], options['1']);
            if (args > 1 && i != argc-1) {
                printf("\n");
            }
        }
    }

    return retSum;
}