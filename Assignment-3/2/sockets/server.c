#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "../helper.h"


int main(int argc, char *argv[])
{
    int link;
    if ((link = socket(AF_UNIX, SOCK_SEQPACKET, 0)) < 0)
    {
        perror("[server] socket creation failure");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un socketAddr;
    memset(&socketAddr, 0, sizeof(socketAddr));
    socketAddr.sun_family = AF_UNIX;
    strcpy(socketAddr.sun_path, SOCKET);

    if (bind(link, (struct sockaddr *) &socketAddr, SUN_LEN(&socketAddr)) == -1)
    {
        perror("[server] couldn't bind to socket");
        exit(EXIT_FAILURE);
    }

    if (listen(link, 3) == -1)
    {
        perror("[server] listening error");
        exit(EXIT_FAILURE);
    }

    if ((link = accept(link, NULL, NULL)) == -1)
    {
        perror("[server] accepting error");
        exit(EXIT_FAILURE);
    }

    char **strings = generateStrings();

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int index = 0;
    while (index < N)
    {
        char *batch = makeBatch(strings, index);
        if (write(link, batch, BATCH_SIZE) == -1)
        {
            perror("[server] couldn't write to socket");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(2*sizeof(char));
        if (read(link, buffer, 2*sizeof(char)) == -1)
        {
            perror("[server] couldn't read-back from socket");
            exit(EXIT_FAILURE);
        }
        else if (toInt(buffer) != index+4)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else printf("Highest ID received at client: %d \n", toInt(buffer));

        index += 5;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %f seconds \n", (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9);

    if (close(link) == -1)
    {
        perror("[server] couldn't close socket");
        exit(EXIT_FAILURE);
    }

    if (unlink(SOCKET) == -1)
    {
        perror("[server] couldn't unlink socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}