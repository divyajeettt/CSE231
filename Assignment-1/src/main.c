#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX_SIZE 256

///////////////////////////////////////////////////////////////////////////////////////////////////

char *strip(char *string) {
    if (string == NULL) {
        return NULL;
    }

    int length = strlen(string);
    char *strippedString = (char *) malloc(length*sizeof(char));

    int x = 0;
    for (int i=0; i < length; i++) {
        if (isspace(string[i]) == 0) {
            strippedString[x++] = string[i];
        }
    }
    strippedString[x] = '\0';

    return strippedString;
}


int isNumeric(char *string) {
    for (int i=0; i < strlen(string); i++) {
        if (isdigit(string[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


int isBuiltin(char *command) {
    char *internal[7] = {"exit", "cd", "echo", "pwd", "type", "help", "crimge"};
    char *external[2] = {"ls", "date"};
    char *hashed[4] = {"cat", "rm", "mkdir", "clear"};

    for (int i=0; i < 7; i++) {
        if (strcmp(command, internal[i]) == 0) {
            return 1;
        }
        if (i < 2 && strcmp(command, external[i]) == 0) {
            return 2;
        }
        if (i < 4 && strcmp(command, hashed[i]) == 0) {
            return 3;
        }
    }
    return 0;
}


int binPath(char *command) {
    if (strcmp(command, "ls") == 0) {
        return 1;
    }
    else if (strcmp(command, "cat") == 0) {
        return 2;
    }
    else if (strcmp(command, "date") == 0) {
        return 3;
    }
    else if (strcmp(command, "rm") == 0) {
        return 4;
    }
    else if (strcmp(command, "mkdir") == 0) {
        return 5;
    }
    else if (strcmp(command, "clear") == 0) {
        return 6;
    }
    return 0;
}


char *join(char *argv[], int argc, char *bin) {
    char *joined = (char *) malloc(MAX_SIZE*sizeof(char));
    strcpy(joined, bin);
    strcat(joined, " ");
    for (int i=1; i < argc; i++) {
        if (i != argc-1) {
            strcat(joined, argv[i]);
            strcat(joined, " ");
        }
    }
    return joined;
}


char *escape(char *string, int *forceStop) {
    char *escaped = (char *) malloc(MAX_SIZE*sizeof(char));
    int processedLast = 0;
    int len = strlen(string) - 1;
    int index = 0;

    for (int i=0; i < len; i++) {
        if (string[i] == '\\') {
            if (string[i+1] == 'a') {
                escaped[index++] = '\a';
            }
            else if (string[i+1] == 'b') {
                escaped[index++] = '\b';
            }
            else if (string[i+1] == 'c') {
                escaped[index++] = '\0';
                *forceStop = 1;
                return escaped;
            }
            else if (string[i+1] == 'e') {
                escaped[index++] = '\e';
            }
            else if (string[i+1] == 'f') {
                escaped[index++] = '\f';
            }
            else if (string[i+1] == 'n') {
                escaped[index++] = '\n';
            }
            else if (string[i+1] == 'r') {
                escaped[index++] = '\r';
            }
            else if (string[i+1] == 't') {
                escaped[index++] = '\t';
            }
            else if (string[i+1] == 'v') {
                escaped[index++] = '\v';
            }
            else if (string[i+1] == '\\') {
                escaped[index++] = '\\';
            }
        }
        else if (string[i-1] != '\\') {
            escaped[index++] = string[i];
        }
    }

    if (string[len-1] != '\\') {
        escaped[index++] = string[len];
    }

    return escaped;
}


int docPath(char *command) {
    if (strcmp(command, "cat") == 0) {
        return 0;
    }
    else if (strcmp(command, "cd") == 0) {
        return 1;
    }
    else if (strcmp(command, "clear") == 0) {
        return 2;
    }
    else if (strcmp(command, "crimge") == 0) {
        return 3;
    }
    else if (strcmp(command, "date") == 0) {
        return 4;
    }
    else if (strcmp(command, "echo") == 0) {
        return 5;
    }
    else if (strcmp(command, "exit") == 0) {
        return 6;
    }
    else if (strcmp(command, "help") == 0) {
        return 7;
    }
    else if (strcmp(command, "ls") == 0) {
        return 8;
    }
    else if (strcmp(command, "mkdir") == 0) {
        return 9;
    }
    else if (strcmp(command, "pwd") == 0) {
        return 10;
    }
    else if (strcmp(command, "rm") == 0) {
        return 11;
    }
    else if (strcmp(command, "type") == 0) {
        return 12;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    char *username = (char *) getlogin();

    printf("oshell-2.3.1 \n");
    printf("login as %s \n", username);

    char *cwd = (char *) malloc(MAX_SIZE*sizeof(char));
    getcwd(cwd, MAX_SIZE);
    cwd = strrchr(cwd, '/') + 1;

    char *binaries[7] = {
        realpath("./bin/main", NULL),
        realpath("./bin/ls", NULL),
        realpath("./bin/cat", NULL),
        realpath("./bin/date", NULL),
        realpath("./bin/rm", NULL),
        realpath("./bin/mkdir", NULL),
        realpath("./bin/clear", NULL),
    };

    char *docs[13] = {
        realpath("./docs/cat.txt", NULL),
        realpath("./docs/cd.txt", NULL),
        realpath("./docs/clear.txt", NULL),
        realpath("./docs/crime.txt", NULL),
        realpath("./docs/date.txt", NULL),
        realpath("./docs/echo.txt", NULL),
        realpath("./docs/exit.txt", NULL),
        realpath("./docs/help.txt", NULL),
        realpath("./docs/ls.txt", NULL),
        realpath("./docs/mkdir.txt", NULL),
        realpath("./docs/pwd.txt", NULL),
        realpath("./docs/rm.txt", NULL),
        realpath("./docs/type.txt", NULL),
    };

    while (1) {
        printf("[%s@oshell %s]$ ", username, cwd);

        char *command = (char *) malloc(MAX_SIZE*sizeof(char));
        if (fgets(command, MAX_SIZE, stdin) == NULL) {
            command = "exit";
        }

        char **args = (char **) calloc(MAX_SIZE, sizeof(char *));
        int countArgs = 0;

        char *token = strip(strtok(command, " "));
        while (token != NULL) {
            if (strcmp(token, "") != 0) {
                args[countArgs++] = token;
            }
            token = strip(strtok(NULL, " "));
        }

        if (countArgs == 0) {
            continue;
        }

        else if (strcmp(args[0], "exit") == 0) {
            // Internal Command (EXTRA)

            if (args[2] != NULL) {
                printf("-bash: exit: too many arguments \n");
                continue;
            }

            if (args[1] != NULL && !isNumeric(args[1])) {
                printf("-bash: exit: %s: numeric argument required \n", args[1]);
            }

            printf("logout \n");
            printf("oshelll-2.3.1 (tty1) \n");

            if (args[1] != NULL) {
                exit(atoi(args[1]));
            }
            else {
                exit(EXIT_SUCCESS);
            }
        }

        else if (strcmp(args[0], "cd") == 0) {
            // Internal Command

            if (args[1] == NULL || (args[1][0] == '-' && args[2] == NULL)) {
                if (chdir(getenv("HOME")) == 0) {
                    strcpy(cwd, "~");
                }
                else {
                    perror("cd");
                }
                continue;
            }

            int option_P = 0;
            int option_L = 0;
            if (args[1] != NULL && args[1][0] == '-') {
                int broken = 0;
                for (int i=1; i < strlen(args[1]); i++) {
                    if (args[1][i] != 'L' && args[1][i] != 'P') {
                        printf("-bash: cd: %c: invalid option \n", args[1][i]);
                        broken = 1;
                        break;
                    }
                    else if (args[1][i] == 'P') {
                        option_P = 1;
                    }
                    else {
                        option_L = 1;
                    }
                }
                if (broken) {
                    continue;
                }
            }

            if (args[2] != NULL && !(option_P || option_L)) {
                printf("-bash: cd: too many arguments \n");
                continue;
            }

            char *changeTo;
            if (option_P) {
                changeTo = realpath(args[2], NULL);
            }
            else {
                changeTo = ((option_L) ? args[2] : args[1]);
            }

            if (chdir(changeTo) == 0) {
                strcpy(cwd, strrchr(getcwd(cwd, MAX_SIZE), '/') + 1);
            }
            else {
                printf("-bash: cd: %s: No such file or directory \n", args[1]);
            }
        }

        else if (strcmp(args[0], "echo") == 0) {
            // Internal Command

            if (args[1] == NULL) {
                printf("\n");
                continue;
            }

            int start = 1;
            int option_n = 0;
            int option_e = 0;

            for (int i=1; i < strlen(args[1]); i++) {
                if (args[1][i] != 'n' && args[1][i] != 'e') {
                    option_e = option_n = 0;
                    start = 1;
                    break;
                }
                else if (args[1][i] == 'n') {
                    option_n = 1;
                    start = 2;
                }
                else {
                    option_e = 1;
                    start = 2;
                }
            }

            char *output = (char *) malloc(MAX_SIZE*sizeof(char));
            int killOutput = 0;
            for (int i=start; i < countArgs; i++) {
                if (option_e) {
                    strcat(output, escape(args[i], &killOutput));
                    if (killOutput) {
                        break;
                    }
                }
                else {
                    strcat(output, args[i]);
                }
                if (i != countArgs-1) {
                    strcat(output, " ");
                }
            }

            if (output != NULL) {
                printf("%s", output);
            }
            if (option_n == 0) {
                printf("\n");
            }
        }

        else if (strcmp(args[0], "pwd") == 0) {
            // Internal Command

            int option_L = 0;
            if (args[1] != NULL && args[1][0] == '-') {
                int broken = 0;
                for (int i=1; i < strlen(args[1]); i++) {
                    if (args[1][i] != 'L' && args[1][i] != 'P') {
                        printf("-bash: pwd: %c: invalid option \n", args[1][i]);
                        broken = 1;
                        break;
                    }
                    else if (args[1][i] == 'L') {
                        option_L = 1;
                    }
                }
                if (broken) {
                    continue;
                }
            }

            char *currentDirectory = (char *) malloc(MAX_SIZE*sizeof(char));
            if (option_L) {
                printf("%s \n", getenv("PWD"));
            }
            else if (getcwd(currentDirectory, MAX_SIZE) != NULL) {
                printf("%s \n", realpath(currentDirectory, NULL));
            }
            else {
                perror("pwd");
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(args[0], "type") == 0) {
            // Internal Command

            if (args[1] == NULL || strcmp(args[1], "") == 0) {
                continue;
            }

            for (int i=1; i < countArgs; i++) {
                int type = isBuiltin(args[i]);
                if (type == 1) {
                    printf("%s is a shell builtin \n", args[i]);
                }
                else if (type == 2) {
                    printf("%s is %s \n", args[i], binaries[binPath(args[i])]);
                }
                else if (type == 3) {
                    printf("%s is hashed (%s) \n", args[i], binaries[binPath(args[i])]);
                }
                else {
                    printf("-bash: type: %s: not found \n", args[i]);
                    continue;
                }
            }
        }

        else if (strcmp(args[0], "help") == 0) {
            // Internal Command

            if (args[1] == NULL || strcmp(args[1], "") == 0) {
                args[1] = "help";
            }

            if (args[2] != NULL) {
                printf("-bash: help: too many arguments \n");
                continue;
            }

            int doc = docPath(args[1]);
            if (doc == -1) {
                printf("-bash: help: no help topics match '%s' \n", args[1]);
            }
            else {
                FILE *doc_file = fopen(docs[doc], "r");
                char character;
                while ((character = fgetc(doc_file)) != EOF) {
                    printf("%c", character);
                }
                fclose(doc_file);
            }
        }

        else if (strcmp(args[0], "crimge") == 0) {
            // Easter-Egg
            if (args[1] != NULL && args[1][0] == '-') {
                printf("-bash: crimge: %s: invalid option \n", args[1]);
                continue;
            }
            printf("OS will be the death of me. O, Shell. OS, Hell. \n");
        }

        else {
            // External Commands
            int bin = binPath(args[0]);
            if (bin == 0) {
                // Invalid Command
                printf("-bash: %s: command not found \n", args[0]);
                continue;
            }
            if (strcmp(args[countArgs-1], "&t") == 0) {
                // pthread_create() and system()
                char *copy = join(args, countArgs, binaries[bin]);
                pthread_t thread_id;
                if (pthread_create(&thread_id, NULL, (void *) &system, copy) == 0) {
                    pthread_join(thread_id, NULL);
                }
                else {
                    perror("pthread");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                // fork() and exec()
                pid_t process_id = fork();
                if (process_id > 0) {
                    // Code to be executed by Parent (wait())
                    int status;
                    if (waitpid(process_id, &status, 0) <= 0) {
                        perror("waitpid");
                        exit(EXIT_FAILURE);
                    }
                }
                else if (process_id == 0) {
                    // Code to be executed by Child (exec())
                    if (execv(binaries[bin], args) == -1) {
                        perror("execv");
                        exit(EXIT_FAILURE);
                    }
                }
                else {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return 0;
}