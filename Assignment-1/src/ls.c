#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int ls(int option_a, int option_1) {
    char *cwd = (char *) malloc(256*sizeof(char));
    getcwd(cwd, 256);

    struct dirent *dir;
    DIR *dirHandler = opendir(cwd);

    if (dirHandler == NULL) {
		exit(EXIT_FAILURE);
	}

    while ((dir = readdir(dirHandler)) != NULL) {
        if (option_a == 0 && dir->d_name[0] == '.') {
			continue;
        }
        printf("%s ", dir->d_name);
        if (option_1 > 0) {
            printf("\n");
        }
    }

    if (option_1 == 0) {
        printf("\n");
    }
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
                printf("ls: invalid option -- %c \n", option);
                return 1;
            }
            options[option]++;
        }
    }

    ls(options['a'], options['1']);

    return 0;
}