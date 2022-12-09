#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../helper.h"


int main(int argc, char *argv[])
{
    key_t key = ftok(SHM, 1);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    int countStrings = 0;
    int countIters = 0;
    while (countStrings <= N)
    {
        char *buffer = (char *) shmat(shmid, NULL, 0);
        countIters++;

        if (countIters%6 == 0)
        {
            char *shm = (char *) shmat(shmid, NULL, 0);
            strcpy(shm, buffer);
            shmdt(shm);
            if (countStrings != N) printf("\n");
        }
        else if (countStrings == N) break;
        else printf("%d: %s \n", countStrings++, buffer);
    }

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}