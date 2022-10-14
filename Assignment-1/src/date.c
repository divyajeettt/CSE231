#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

///////////////////////////////////////////////////////////////////////////////////////////////////

int getDate(int option_I, int option_R, int option_u) {
    time_t now = time(0);
    struct tm *ts = localtime(&now);

    char *buffer = (char *) malloc(MAX_SIZE*sizeof(char));

    if (option_I) {
        strftime(buffer, MAX_SIZE, "%Y-%m-%d", ts);
    }
    else if (option_R) {
        strftime(buffer, MAX_SIZE, "%a, %d %b %Y %H:%M:%S %z", ts);
    }
    else if (option_u) {
        strftime(buffer, MAX_SIZE, "%a %b %d %I:%M:%S %p UTC %Y", gmtime(&now));
    }
    else {
        strftime(buffer, MAX_SIZE, "%a %b %d %I:%M:%S %p %Z %Y", ts);
    }

    if (buffer != NULL) {
        printf("%s\n", buffer);
        return 0;
    }
    else {
        return 1;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int *options = (int *) calloc(MAX_SIZE, sizeof(int));

    for (int i=1; i < argc; i++) {
        if (argv[i][0] != '-') {
            printf("date: invalid date -- '%s' \n", argv[i]);
            return 1;
        }
        for (int j=1; j < strlen(argv[i]); j++) {
            char option = argv[i][j];
            if (option != 'I' && option != 'R' && option != 'u') {
                printf("date: invalid option -- '%c' \n", option);
                return 1;
            }
            if (options[option] == 1) {
                printf("date: multiple output formats specified \n");
                return 1;
            }
            options[option]++;
        }
    }

    int I = options['I'];
    int R = options['R'];
    int u = options['u'];
    if ((I && R) || (R && u) || (u && I) || (I && R && u)) {
        printf("date: multiple output formats specified \n");
        return 1;
    }

    return getDate(options['I'], options['R'], options['u']);
}