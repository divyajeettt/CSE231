#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "../helper.h"


struct Philospher philosophers[N];
struct Fork forks[N];


void *eat(void *arg)
{
    int i = *((int *) arg);
    // printf("Philosopher %d: Thinking \n", i);

    pthread_mutex_lock(&forks[LEFT].lock);
    pthread_mutex_lock(&forks[RIGHT].lock);

    // printf("Philosopher %d: Eating \n", i);
    philosophers[i].eaten++;

    pthread_mutex_unlock(&forks[LEFT].lock);
    pthread_mutex_unlock(&forks[RIGHT].lock);
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
        if (pthread_mutex_destroy(&forks[i].lock) != 0)
        {
            printf("Mutex destroy failed \n");
            exit(EXIT_FAILURE);
        }
        printf("Philosopher %d: Eaten %lld times \n", i, philosophers[i].eaten);
    }

    return 0;
}