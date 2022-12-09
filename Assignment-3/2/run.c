#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256


char *getServer(char *path)
{
    static char server[BUFFER_SIZE];
    sprintf(server, "./2/%s/server", path);
    return server;
}


char *getClient(char *path)
{
    static char client[BUFFER_SIZE];
    sprintf(client, "./2/%s/client", path);
    return client;
}


int main(int argc, char *argv[])
{
    pid_t process_id = fork();

    if (process_id > 0)
    {
        if (execl(getServer(argv[1]), (char *) NULL) == -1)
        {
            perror("execl (server)");
            exit(EXIT_FAILURE);
        }
    }
    else if (process_id == 0)
    {
        sleep(1);
        if (execl(getClient(argv[1]), (char *) NULL) == -1)
        {
            perror("execl (client)");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}