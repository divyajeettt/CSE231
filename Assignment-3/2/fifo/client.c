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
    while (countStrings < N)
    {
        if ((linkReader = open(FIFO_S2C, O_RDONLY)) == -1)
        {
            perror("[client] FIFO_S2C opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(BATCH_SIZE*sizeof(char));
        if (read(linkReader, buffer, BATCH_SIZE) == -1)
        {
            perror("[client] couldn't read from FIFO_S2C");
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

        if (close(linkReader) == -1)
        {
            perror("[client] couldn't close FIFO_S2C");
            exit(EXIT_FAILURE);
        }

        if ((linkWriter = open(FIFO_C2S, O_WRONLY)) == -1)
        {
            perror("[client] FIFO_C2S opening failure");
            exit(EXIT_FAILURE);
        }

        if (write(linkWriter, indexed[0], 2*sizeof(char)) == -1)
        {
            perror("[client] couldn't write-back to FIFO_C2S");
            exit(EXIT_FAILURE);
        }
        else printf("\n");

        if (close(linkWriter) == -1)
        {
            perror("[client] couldn't close FIFO_C2S");
            exit(EXIT_FAILURE);
        }
    }

    if (unlink(FIFO_C2S) == -1)
    {
        perror("[server] couldn't unlink FIFO_C2S");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}