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
        perror("[client] socket opening failure");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un socketAddr;
    memset(&socketAddr, 0, sizeof(socketAddr));
    socketAddr.sun_family = AF_UNIX;
    strcpy(socketAddr.sun_path, SOCKET);

    if (connect(link, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) == -1)
    {
        perror("[client] couldn't connect to socket");
        exit(EXIT_FAILURE);
    }

    int countStrings = 0;
    while (countStrings < N)
    {
        char *buffer = (char *) malloc(BATCH_SIZE);
        if (read(link, buffer, BATCH_SIZE) == -1)
        {
            perror("[client] couldn't read from socket");
            exit(EXIT_FAILURE);
        }

        char **strings = splitBatch(buffer);
        char **indexed;
        for (int i=0; i < CHUNK; i++)
        {
            indexed = splitIndex(strings[i]);
            printf("%d: %s\n", toInt(indexed[0]), indexed[1]);
            countStrings++;
        }

        if (write(link, indexed[0], 2*sizeof(char)) == -1)
        {
            perror("[client] couldn't write-back to socket");
            exit(EXIT_FAILURE);
        }
        else printf("\n");
    }

    if (close(link) == -1)
    {
        perror("[client] couldn't close socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}