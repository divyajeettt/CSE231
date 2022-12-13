#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "../helper.h"


struct Philosopher philosophers[N];
struct Fork forks[N];


void *eat(void *arg)
{
    int i = *((int *) arg);

    sem_wait(&forks[FIRST].semaphore);
    sem_wait(&forks[SECOND].semaphore);

    philosophers[i].eaten++;

    sem_post(&forks[FIRST].semaphore);
    sem_post(&forks[SECOND].semaphore);
}


int main()
{
    for (int i = 0; i < N; i++)
    {
        forks[i] = makeFork();
        philosophers[i] = makePhilosopher();
    }

    for (long long j = 0; j < 10000; j++)
    {
        for (int i = 0; i < N; i++)
        {
            int *arg = (int *) malloc(sizeof(int));
            *arg = i;
            pthread_create(&philosophers[i].thread, NULL, eat, (void *) arg);
        }
        for (int i = 0; i < N; i++)
        {
            pthread_join(philosophers[i].thread, NULL);
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (sem_destroy(&forks[i].semaphore) != 0)
        {
            perror("sem_destroy");
            exit(EXIT_FAILURE);
        }
        printf("Philosopher %d: Eaten %lld times \n", i, philosophers[i].eaten);
    }

    return 0;
}