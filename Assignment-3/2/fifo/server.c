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
    mkfifo(FIFO, 0666);

    int link;
    if ((link = open(FIFO, O_RDWR)) == -1)
    {
        perror("[server] fifo opening failure");
        exit(EXIT_FAILURE);
    }

    char **strings = generateStrings();
    clock_t start = clock();

    int index = 0;
    while (index < N)
    {
        for (int i=0; i < CHUNK; i++)
        {
            if (write(link, strings[index++], LENGTH+1) == -1)
            {
                perror("[server] couldn't write to fifo");
                exit(EXIT_FAILURE);
            }
        }

        if (write(link, toString(index-1), sizeof(int)+1) == -1)
        {
            perror("[server] couldn't write end-index to fifo");
            exit(EXIT_FAILURE);
        }

        char *buffer = (char *) malloc(2*sizeof(char));
        if (read(link, buffer, 2) == -1)
        {
            perror("[server] couldn't read from fifo");
            exit(EXIT_FAILURE);
        }
    }
}