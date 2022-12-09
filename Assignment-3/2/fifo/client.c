#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../helper.h"


int main()
{
    int link;
    mkfifo(FIFO, 0666);

    int countStrings = 0;
    int countIters = 0;
    while (countStrings <= N)
    {
        if ((link = open(FIFO, O_RDONLY)) == -1)
        {
            perror("[client] fifo (read-only) opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(LENGTH*sizeof(char));
        if (read(link, buffer, LENGTH) == -1)
        {
            perror("[client] couldn't read from fifo");
            exit(EXIT_FAILURE);
        }
        countIters++;

        if (countIters%6 == 0)
        {
            if (close(link) == -1)
            {
                perror("[client] couldn't close fifo (read-only)");
                exit(EXIT_FAILURE);
            }

            if ((link = open(FIFO, O_WRONLY)) == -1)
            {
                perror("[client] fifo (write-only) opening failure");
                exit(EXIT_FAILURE);
            }

            if (write(link, buffer, 2) == -1)
            {
                perror("[client] couldn't write-back to fifo");
                exit(EXIT_FAILURE);
            }
            if (countStrings != N) printf("\n");

            if (close(link) == -1)
            {
                perror("[client] couldn't close fifo (write-only)");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (countStrings == N) break;
            else printf("%d: %s \n", countStrings++, buffer);

            if (close(link) == -1)
            {
                perror("[client] couldn't close fifo (read-only)");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (unlink(FIFO) == -1)
    {
        perror("[client] unable to close fifo");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}