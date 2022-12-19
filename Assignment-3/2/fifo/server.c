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
        char *batch = makeBatch(strings, index);
        if ((linkWriter = open(FIFO_S2C, O_WRONLY)) == -1)
        {
            perror("[server] FIFO_S2C opening failure");
            exit(EXIT_FAILURE);
        }
        if (write(linkWriter, batch, BATCH_SIZE) == -1)
        {
            perror("[server] couldn't write to FIFO_S2C");
            exit(EXIT_FAILURE);
        }

        if (close(linkWriter) == -1)
        {
            perror("[server] couldn't close FIFO_S2C");
            exit(EXIT_FAILURE);
        }

        if ((linkReader = open(FIFO_C2S, O_RDONLY)) == -1)
        {
            perror("[server] FIFO_C2S opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(2*sizeof(char));
        if (read(linkReader, buffer, 2*sizeof(char)) == -1)
        {
            perror("[server] couldn't read-back from FIFO_C2S");
            exit(EXIT_FAILURE);
        }
        else if (toInt(buffer) != index+4)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else printf("Highest ID received at client: %d \n", toInt(buffer));

        if (close(linkReader) == -1)
        {
            perror("[server] couldn't close FIFO_C2S");
            exit(EXIT_FAILURE);
        }

        index += 5;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %f seconds \n", (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9);

    if (unlink(FIFO_S2C) == -1)
    {
        perror("[server] couldn't unlink FIFO_S2C");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}