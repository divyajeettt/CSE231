#include <time.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int getDate(int option_I, int option_R) {
    time_t now;
    struct tm *ts = localtime(&now);

    char *buffer = (char *) malloc(256*sizeof(char));

    if (option_I > 0) {
        strftime(buffer, 256, "%Y-%m-%d", ts);
    }
    else if (option_R > 0) {
        strftime(buffer, 256, "%a, %d %b %Y %H:%M:%S %z", ts);
    }
    else {
        strftime(buffer, 256, "%a %b %d %I:%M:%S %p %Z %Y", ts);
    }

    if (buffer == NULL) {
        return 1;
    }
    else {
        printf("%s\n", buffer);
        return 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    int *options = (int *) calloc(256, sizeof(int));

    for (int i=0; i < argc; i++) {
        if (argv[i][0] != '-') {
            printf("date: invalid date -- '%s' \n", argv[i]);
            return 1;
        }
        for (int j=1; j < strlen(argv[i]); j++) {
            char option = argv[i][j];
            if (option != 'I' && option != 'R') {
                printf("date: invalid option -- '%c' \n", option);
                return 1;
            }
            options[option]++;
        }
    }

    if (options['I']*options['R'] > 0) {
        printf("date: multiple output formats specified \n");
        return 1;
    }

    return getDate(options['I'], options['R']);
}