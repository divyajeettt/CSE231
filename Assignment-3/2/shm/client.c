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
    if ((shmid = shmget(key, SHM_SIZE, 0666)) == -1)
    {
        perror("[client] couldn't access shared memory");
        exit(EXIT_FAILURE);
    }

    int countStrings = 0;
    int countIters = 0;
    while (countStrings <= N)
    {
        char *buffer = (char *) shmat(shmid, NULL, 0);
        char **strings = parseMessage(buffer);

        for (int i=0; i < CHUNK; i++) printf("%d: %s \n", countStrings++, strings[i]);
        shmdt(buffer);

        char *shm = (char *) shmat(shmid, NULL, 0);
        strcpy(shm, strings[5]);
        while (strlen(shm) == LENGTH);
        shmdt(shm);
    }

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}