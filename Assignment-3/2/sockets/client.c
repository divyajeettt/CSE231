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
        perror("socket opening failure");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un socketAddr;
    memset(&socketAddr, 0, sizeof(socketAddr));
    socketAddr.sun_family = AF_UNIX;
    strcpy(socketAddr.sun_path, SOCKET);

    if (connect(link, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) == -1)
    {
        perror("couldn't connect to socket");
        exit(EXIT_FAILURE);
    }

    int countStrings = 0;
    int countIters = 0;
    while (countStrings <= N)
    {
        char *buffer = (char *) malloc(LENGTH*sizeof(char));
        if (read(link, buffer, LENGTH) == -1)
        {
            perror("client unable to read from socket");
            exit(EXIT_FAILURE);
        }
        countIters++;

        if (countIters%6 == 0)
        {
            if (write(link, buffer, 2) == -1)
            {
                perror("client unable to write-back to socket");
                exit(EXIT_FAILURE);
            }
            if (countStrings != N) printf("\n");
        }
        else if (countStrings == N) break;
        else printf("%d: %s \n", countStrings++, buffer);
    }

    if (close(link) == -1)
    {
        perror("client unable to close socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}