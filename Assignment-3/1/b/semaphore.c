#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../helper.h"


struct Philosopher philosophers[N];
struct SauceBowl bowls[2];
struct Fork forks[N];


void *philosophize(void *arg)
{
    int i = *((int *) arg);
    while (1)
    {
        think(&philosophers[i]);

        int CHOSEN = rand() % 2;

        sem_wait(&bowls[CHOSEN].semaphore);
        sem_wait(&forks[FIRST].semaphore);
        sem_wait(&forks[SECOND].semaphore);

        eat(&philosophers[i]);

        sem_post(&bowls[CHOSEN].semaphore);
        sem_post(&forks[FIRST].semaphore);
        sem_post(&forks[SECOND].semaphore);
    }
}


int main()
{
    for (int i = 0; i < 2; i++)
    {
        bowls[i] = makeSauceBowl();
    }

    for (int i = 0; i < N; i++)
    {
        forks[i] = makeFork();
        philosophers[i] = makePhilosopher(i);
    }

    for (int i = 0; i < N; i++)
    {
        int *arg = (int *) malloc(sizeof(int));
        *arg = i;
        pthread_create(&philosophers[i].thread, NULL, philosophize, (void *) arg);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i].thread, NULL);
    }

    return 0;
}