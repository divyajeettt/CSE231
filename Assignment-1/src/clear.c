#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (argv[1][0] == '-') {
            printf("clear: invalid option -- '%s' \n", argv[1]);
        }
        else {
            printf("Usage: clear \n");
        }
    }
    else {
        printf("\e[1;1H\e[2J");
    }
}