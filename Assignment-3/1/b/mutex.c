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
        int CHOSEN = think(&philosophers[i]);

        pthread_mutex_lock(&bowls[CHOSEN].lock);
        pthread_mutex_lock(&forks[FIRST].lock);
        pthread_mutex_lock(&forks[SECOND].lock);

        eat(&philosophers[i]);

        pthread_mutex_unlock(&bowls[CHOSEN].lock);
        pthread_mutex_unlock(&forks[FIRST].lock);
        pthread_mutex_unlock(&forks[SECOND].lock);
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