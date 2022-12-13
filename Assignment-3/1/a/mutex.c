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

    int first, second;
    if (i%2 == 0) {
        first = LEFT; second = RIGHT;
    } else {
        first = RIGHT; second = LEFT;
    }

    pthread_mutex_lock(&forks[first].lock);
    pthread_mutex_lock(&forks[second].lock);

    philosophers[i].eaten++;

    pthread_mutex_unlock(&forks[first].lock);
    pthread_mutex_unlock(&forks[second].lock);
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
        if (pthread_mutex_destroy(&forks[i].lock) != 0)
        {
            perror("pthread_mutex_destroy");
            exit(EXIT_FAILURE);
        }
        printf("Philosopher %d: Eaten %lld times \n", i, philosophers[i].eaten);
    }

    return 0;
}