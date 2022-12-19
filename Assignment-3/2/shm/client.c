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
    if ((shmid = shmget(key, BATCH_SIZE, 0666)) == -1)
    {
        perror("[client] couldn't access shared memory");
        exit(EXIT_FAILURE);
    }

    int countStrings = 0;
    while (countStrings < N)
    {
        char *buffer;
        if ((buffer = (char *) shmat(shmid, NULL, 0)) == ((void *) -1))
        {
            perror("[client] couldn't attach to O_RDONLY shared memory");
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

        if (shmdt(buffer) == -1)
        {
            perror("[client] couldn't detach from O_RDONLY shared memory");
            exit(EXIT_FAILURE);
        }
        else printf("\n");

        char *shm;
        if ((shm = (char *) shmat(shmid, NULL, 0)) == ((void *) -1))
        {
            perror("[client] couldn't attach to O_WRONLY shared memory");
            exit(EXIT_FAILURE);
        }

        strcpy(shm, indexed[0]);
        if (countStrings != N) while (strcmp(shm, indexed[0]) == 0);

        if (shmdt(shm) == -1)
        {
            perror("[client] couldn't detach from O_WRONLY shared memory");
            exit(EXIT_FAILURE);
        }
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("[client] couldn't remove shared memory");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}