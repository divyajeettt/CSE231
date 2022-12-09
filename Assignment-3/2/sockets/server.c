#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "../helper.h"


int main(int argc, int *argv[])
{
    int link;
    if ((link = socket(AF_UNIX, SOCK_SEQPACKET, 0)) < 0)
    {
        perror("socket creation failure");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un socketAddr;
    memset(&socketAddr, 0, sizeof(socketAddr));
    socketAddr.sun_family = AF_UNIX;
    strcpy(socketAddr.sun_path, SOCKET);

    if (bind(link, (struct sockaddr *) &socketAddr, SUN_LEN(&socketAddr)) == -1)
    {
        perror("couldn't bind to socket");
        exit(EXIT_FAILURE);
    }

    if (listen(link, 3) == -1)
    {
        perror("server listening error");
        exit(EXIT_FAILURE);
    }

    if ((link = accept(link, NULL, NULL)) == -1)
    {
        perror("server accepting error");
        exit(EXIT_FAILURE);
    }

    clock_t start = clock();

    char **strings = generateStrings();
    int index = 0;
    while (index < N)
    {
        for (int i=0; i < CHUNK; i++)
        {
            if (write(link, strings[index++], LENGTH+1) == -1)
            {
                perror("server unable to write to socket");
                exit(EXIT_FAILURE);
            }
        }

        if (write(link, toString(index-1), sizeof(int)+1) == -1)
        {
            perror("server unable to write end-index to socket");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(LENGTH * sizeof(char));
        if (read(link, buffer, sizeof(buffer)) == -1)
        {
            perror("server unable to read-back from socket");
            exit(EXIT_FAILURE);
        }
        else if (toInt(buffer) != index-1)
        {
            printf("CRITICAL ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Highest ID received at client: %d \n", toInt(buffer));
        }
    }

    clock_t end = clock();
    printf("Time taken: %f seconds \n", ((double) (end-start) / CLOCKS_PER_SEC));

    if (close(link) == -1)
    {
        perror("server unable to close socket");
        exit(EXIT_FAILURE);
    }

    if (unlink(SOCKET) == -1)
    {
        perror("client unable to unlink socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}