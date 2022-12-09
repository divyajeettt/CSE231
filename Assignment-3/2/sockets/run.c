#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    pid_t process_id = fork();
    if (process_id > 0)
    {
        if (execl("./2/sockets/server", (char *) NULL) == -1)
        {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }
    else if (process_id == 0)
    {
        sleep(1);
        if (execl("./2/sockets/client", (char *) NULL) == -1)
        {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}