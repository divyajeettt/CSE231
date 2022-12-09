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
    int link;
    mkfifo(FIFO, 0666);

    char **strings = generateStrings();
    clock_t start = clock();

    int index = 0;
    while (index < N)
    {
        if ((link = open(FIFO, O_WRONLY)) == -1)
        {
            perror("[server] fifo (write-only) opening failure");
            exit(EXIT_FAILURE);
        }

        for (int i=0; i < CHUNK; i++)
        {
            if (write(link, strings[index++], LENGTH+1) == -1)
            {
                perror("[server] couldn't write to fifo");
                exit(EXIT_FAILURE);
            }
            sleep(1);
        }

        if (write(link, toString(index-1), sizeof(int)+1) == -1)
        {
            perror("[server] couldn't write end-index to fifo");
            exit(EXIT_FAILURE);
        }

        if (close(link) == -1)
        {
            perror("[server] couldn't close fifo (write-only)");
            exit(EXIT_FAILURE);
        }

        if ((link = open(FIFO, O_RDONLY)) == -1)
        {
            perror("[server] fifo (read-only) opening failure");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(LENGTH*sizeof(char));
        if (read(link, buffer, LENGTH) == -1)
        {
            perror("[server] couldn't read-back from fifo (read-only)");
            exit(EXIT_FAILURE);
        }
        else if (toInt(buffer) != index-1)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Highest ID received at client: %d \n", toInt(buffer));
        }

        if (close(link) == -1)
        {
            perror("[server] couldn't close fifo (read-only)");
            exit(EXIT_FAILURE);
        }
    }

    clock_t end = clock();
    printf("Time taken: %f seconds \n", ((double) (end-start) / CLOCKS_PER_SEC));

    if (unlink(FIFO) == -1)
    {
        perror("[server] couldn't unlink fifo");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}