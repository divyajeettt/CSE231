#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "../helper.h"


struct Philospher philosophers[N];
struct Fork forks[N];


void *eat(void *arg)
{
    int i = *((int *) arg);
    // printf("Philosopher %d: Thinking \n", i);

    sem_wait(&forks[LEFT].semaphore);
    sem_wait(&forks[RIGHT].semaphore);

    // printf("Philosopher %d: Eating \n", i);
    philosophers[i].eaten++;

    sem_post(&forks[LEFT].semaphore);
    sem_post(&forks[RIGHT].semaphore);
}


int main()
{
    int i;

    for (i = 0; i < N; i++)
    {
        forks[i] = makeFork();
        philosophers[i] = makePhilosopher();
    }

    for (long long j = 0; j < 10000; j++)
    {
        for (i = 0; i < N; i++)
        {
            pthread_create(&philosophers[i].thread, NULL, eat, (void *) &i);
        }
        for (i = 0; i < N; i++)
        {
            pthread_join(philosophers[i].thread, NULL);
        }
    }

    for (i = 0; i < N; i++)
    {
        if (sem_destroy(&forks[i].semaphore) != 0)
        {
            printf("Semaphore destroy failed \n");
            exit(EXIT_FAILURE);
        }
        printf("Philosopher %d: Eaten %lld times \n", i, philosophers[i].eaten);
    }

    return 0;
}