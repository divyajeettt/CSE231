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
    if ((shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT)) == -1)
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
        char *batch = (char *) malloc((LENGTH+1)*CHUNK*sizeof(char));
        for (int i=0; i < CHUNK; i++) strcat(batch, strings[index++]);
        strcat(batch, toString(index-1));

        char *shm = (char *) shmat(shmid, NULL, 0);
        strcpy(shm, batch);
        shmdt(shm);

        char *buffer = (char *) shmat(shmid, NULL, 0);
        while (strlen(buffer) != LENGTH);

        if (toInt(buffer) != index-1)
        {
            printf("ID ERROR: received ID %d; expected ID %d \n", toInt(buffer), index-1);
            exit(EXIT_FAILURE);
        }
        else printf("Highest ID received at client: %d \n", toInt(buffer));
        shmdt(buffer);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time taken: %f seconds \n", (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9);

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}