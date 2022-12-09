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

    char **strings = generateStrings();
    clock_t start = clock();

    int shmid;
    if ((shmid = shmget(key, 1024, 0666|IPC_CREAT)) == -1)
    {
        perror("[server] couldn't create shared memory");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while (index < N)
    {
        for (int i=0; i < CHUNK; i++)
        {
            char *shm = (char *) shmat(shmid, NULL, 0);
            strcpy(shm, strings[index++]);
            shmdt(shm);
            sleep(1);
        }

        char *buffer = (char *) shmat(shmid, NULL, 0);
        if (toInt(buffer) != index-1)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Highest ID received at client: %d \n", toInt(buffer));
        }
    }

    clock_t end = clock();
    double time_spent = (double) (end-start) / CLOCKS_PER_SEC;
    printf("Time spent: %f", time_spent);

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}