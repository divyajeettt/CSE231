#include <time.h>
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
    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    char **strings = generateStrings();

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int index = 0;
    while (index < N)
    {
        if ((linkWriter = open(FIFO_S2C, O_WRONLY)) == -1)
        {
            perror("[server] fifo (write-only) opening failure");
            exit(EXIT_FAILURE);
        }

        for (int i=0; i < CHUNK; i++)
        {
            if (write(linkWriter, strings[index++], LENGTH) == -1)
            {
                perror("[server] couldn't write to fifo (write-only)");
                exit(EXIT_FAILURE);
            }
            usleep(1e3);
        }

        if (write(linkWriter, toString(index-1), sizeof(int)) == -1)
        {
            perror("[server] couldn't write end-index to fifo (write-only)");
            exit(EXIT_FAILURE);
        }
        usleep(1e3);

        if (close(linkWriter) == -1)
        {
            perror("[server] couldn't close fifo (write-only)");
            exit(EXIT_FAILURE);
        }

        if ((linkReader = open(FIFO_C2S, O_RDONLY)) == -1)
        {
            perror("[server] fifo (read-only) opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(LENGTH*sizeof(char));
        if (read(linkReader, buffer, sizeof(buffer)) == -1)
        {
            perror("[server] couldn't read-back from fifo (read-only)");
            exit(EXIT_FAILURE);
        }
        else if (toInt(buffer) != index-1)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else printf("Highest ID received at client: %d \n", toInt(buffer));

        if (close(linkReader) == -1)
        {
            perror("[server] couldn't close fifo (read-only)");
            exit(EXIT_FAILURE);
        }
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %f seconds \n", (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9);

    if (unlink(FIFO_C2S) == -1)
    {
        perror("[server] couldn't unlink fifo (read-only)");
        exit(EXIT_FAILURE);
    }

    if (unlink(FIFO_S2C) == -1)
    {
        perror("[server] couldn't unlink fifo (write-only)");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}