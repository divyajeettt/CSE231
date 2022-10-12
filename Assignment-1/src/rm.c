#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int rm(char *name, int option_r, int option_i, int option_v, int showResult) {

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
            if (option != 'r' && option != 'R' && option != 'i' && option != 'v') {
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
            retSum += rm(argv[i], options['r']+options['R'], options['i'], options['v'], 1);
        }
    }

    return retSum;
}

// rm -rR -i -v