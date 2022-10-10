#include <stdio.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Starting the Shell
    
    while (1) {
        char command[256];

        printf("[oshell] $ ");
        fgets(command, stdin);
    }

    return 0;
}
