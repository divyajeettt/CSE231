#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

char *strip(char *string) {
    int length = strlen(string);
    char *strippedString = (char *) malloc(length*sizeof(char));

    int x = 0;
    for (int i=0; i < length; i++) {
        if (isspace(string[i]) == 0)
            strippedString[x++] = string[i];
    }
    strippedString[x] = '\0';

    return strippedString;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // Starting the Shell
    int maxSize = 256;

    char *username = (char *) malloc(maxSize*sizeof(char));
    username = (char *) getlogin();

    while (1) {
        printf("[dvgt@oshell] $ ", username);

        char *command = (char *) malloc(maxSize*sizeof(char));
        fgets(command, maxSize, stdin);

        char *token = strip(strtok(command, " "));

        if (strcmp(token, "") == 0) {
            continue;
        }

        else if (strcmp(token, "exit") == 0) {
            // Internal Command (EXTRA)
            exit(0);
        }

        else if (strcmp(token, "cd") == 0) {
            // Internal Command
            printf("Detected command: cd \n");
        }

        else if (strcmp(token, "echo") == 0) {
            // Internal Command

            int flag = 1;

            token = strtok(NULL, " ");

            if (strcmp(token, "-n") == 0)
                flag = 0;

            while (token != NULL) {
                printf("%s ", strip(token));
                token = strtok(NULL, " ");
            }

            if (flag) {
                printf("\n");
            }
        }

        else if (strcmp(token, "pwd") == 0) {
            // Internal Command
            printf("Detected command: pwd \n");
        }

        else if (strcmp(token, "ls") == 0) {
            // External Command
            printf("Detected command: ls \n");
        }

        else if (strcmp(token, "cat") == 0) {
            // External Command
            printf("Detected command: cat \n");
        }

        else if (strcmp(token, "date") == 0) {
            // External Command
            printf("Detected command: date \n");
        }

        else if (strcmp(token, "rm") == 0) {
            // External Command
            printf("Detected command: rm \n");
        }

        else if (strcmp(token, "mkdir") == 0) {
            // External Command
            printf("Detected command: mkdir \n");
        }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // EXTRAS

        else if (strcmp(token, "type") == 0) {
            // Internal Command
            printf("Detected command: type \n");
        }

        else if (strcmp(token, "help") == 0) {
            // External Command
            printf("Detected command: help \n");
        }

        else if (strcmp(token, "crimge") == 0) {
            // Easter-Egg
            printf("OS will be the death of me. O, Shell. OS, Hell. \n");
        }

        else {
            // Invalid Command
            printf("-bash: %s: command not found \n", token);
        }
    }

    return 0;
}
