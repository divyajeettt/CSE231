#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../helper.h"


struct Philosopher philosophers[N];
struct Fork forks[N];


void *philosophize(void *arg)
{
    int i = *((int *) arg);
    while (1)
    {
        think(&philosophers[i]);
        pthread_mutex_lock(&forks[FIRST].lock);
        pthread_mutex_lock(&forks[SECOND].lock);

        eat(&philosophers[i]);
        pthread_mutex_unlock(&forks[FIRST].lock);
        pthread_mutex_unlock(&forks[SECOND].lock);
    }
}


int main()
{
    for (int i = 0; i < N; i++)
    {
        forks[i] = makeFork();
        philosophers[i] = makePhilosopher(i);
    }

    for (int i = 0; i < N; i++) pthread_create(&philosophers[i].thread, NULL, philosophize, (void *) &philosophers[i].id);
    for (int i = 0; i < N; i++) pthread_join(philosophers[i].thread, NULL);

    return 0;
}