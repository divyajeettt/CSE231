#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Starting the Shell

    while (1) {
        char *command = (char *) malloc(10*sizeof(char));

        printf("[oshell] $ ");
        fgets(command, 10, stdin);

        char *token = strtok(command, " ");
        // while (token != NULL) {
        //     printf("%s\n", token);
        //     token = strtok(NULL, " ");
        // }

        if (strcmp(token, "exit\n") == 0)
            exit(0);

        else if (strcmp(token, "cd") == 0) {
            // Internal Command
        }

        else if (strcmp(token, "echo") == 0) {
            // Internal Command
        }

        else if (strcmp(token, "pwd") == 0) {
            // Internal Command
        }

        else if (strcmp(token, "ls") == 0) {
            // External Command
        }

        else if (strcmp(token, "cat") == 0) {
            // External Command
        }

        else if (strcmp(token, "date") == 0) {
            // External Command
        }

        else if (strcmp(token, "rm") == 0) {
            // External Command
        }

        else if (strcmp(token, "mkdir") == 0) {
            // External Command
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // EXTRAS

        else if (strcmp(token, "type") == 0) {
            // Internal Command
        }

        else if (strcmp(token, "help") == 0) {
            // External Command
        }

        else {
            printf("-bash: %s: command not found \n", token);
        }
    }

    return 0;
}
