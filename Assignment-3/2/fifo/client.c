#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../helper.h"


int main(int argc, char *argv[])
{
    int linkReader, linkWriter;
    mkfifo(FIFO_S2C, 0666);
    mkfifo(FIFO_C2S, 0666);

    int countStrings = 0;
    int countIters = 0;
    while (countStrings <= N)
    {
        if ((linkReader = open(FIFO_S2C, O_RDONLY)) == -1)
        {
            perror("[client] fifo (read-only) opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(LENGTH*sizeof(char));
        if (read(linkReader, buffer, sizeof(buffer)+2) == -1)
        {
            perror("[client] couldn't read from fifo (read-only)");
            exit(EXIT_FAILURE);
        }
        countIters++;

        if (close(linkReader) == -1)
        {
            perror("[client] couldn't close fifo (read-only)");
            exit(EXIT_FAILURE);
        }

        if (countIters%6 != 0)
        {
            if (countStrings == N) break;
            else printf("%d: %s \n", countStrings++, buffer);
        }
        else
        {
            if ((linkWriter = open(FIFO_C2S, O_WRONLY)) == -1)
            {
                perror("[client] fifo (write-only) opening failure");
                exit(EXIT_FAILURE);
            }

            if (write(linkWriter, buffer, sizeof(buffer)+2) == -1)
            {
                perror("[client] couldn't write-back to fifo (write-only)");
                exit(EXIT_FAILURE);
            }
            if (countStrings != N) printf("\n");

            if (close(linkWriter) == -1)
            {
                perror("[client] couldn't close fifo (write-only)");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (unlink(FIFO_S2C) == -1)
    {
        perror("[server] couldn't unlink fifo (read-only)");
        exit(EXIT_FAILURE);
    }

    if (unlink(FIFO_C2S) == -1)
    {
        perror("[server] couldn't unlink fifo (write-only)");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}