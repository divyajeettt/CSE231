#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../helper.h"


int main(int argc, char *argv[])
{
    key_t key = ftok(SHM, 1);

    int shmid;
    if ((shmid = shmget(key, BATCH_SIZE, 0666|IPC_CREAT)) == -1)
    {
        perror("[server] couldn't access shared memory");
        exit(EXIT_FAILURE);
    }

    char **strings = generateStrings();

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    int index = 0;
    while (index < N)
    {
        char *batch = makeBatch(strings, index);

        char *shm;
        if ((shm = (char *) shmat(shmid, NULL, 0)) == ((void *) -1))
        {
            perror("[server] couldn't attach to O_WRONLY shared memory");
            exit(EXIT_FAILURE);
        }
        strcpy(shm, batch);

        if (shmdt(shm) == -1)
        {
            perror("[server] couldn't detach from O_WRONLY shared memory");
            exit(EXIT_FAILURE);
        }

        char *buffer;
        if ((buffer = (char *) shmat(shmid, NULL, 0)) == ((void *) -1))
        {
            perror("[server] couldn't attach to O_RDONLY shared memory");
            exit(EXIT_FAILURE);
        }
        while (strcmp(buffer, batch) == 0);

        if (toInt(buffer) != index+4)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else printf("Highest ID received at client: %d \n", toInt(buffer));

        if (shmdt(buffer) == -1)
        {
            perror("[server] couldn't detach from O_RDONLY shared memory");
            exit(EXIT_FAILURE);
        }

        index += 5;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %f seconds \n", (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9);

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}