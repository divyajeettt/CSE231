#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int ls(char *dirName, int option_a, int option_1) {
    if (dirName == "") {
        char *dirName = (char *) malloc(256*sizeof(char));
        getcwd(dirName, 256);
    }

    DIR *dirHandler = opendir(dirName);

    if (dirHandler == NULL) {
        if (errno = ENOENT) {
            printf("ls: cannot access '%s': No such file or directory \n", dirName);
		}
        return 1;
		// exit(EXIT_FAILURE);
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
    // printf("OH MA G INSIDE %s \n", argv[0]);

    int *options = (int *) malloc(256*sizeof(int));

    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
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

    int retSum = 0;
    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            retSum += ls(argv[i], options['a'], options['1']);
        }
    }

    return retSum;
}