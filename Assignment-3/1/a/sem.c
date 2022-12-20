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
        sem_wait(&forks[FIRST].semaphore);
        sem_wait(&forks[SECOND].semaphore);

        eat(&philosophers[i], forks[FIRST], forks[SECOND], NULL);
        sem_post(&forks[FIRST].semaphore);
        sem_post(&forks[SECOND].semaphore);
    }
}


int main()
{
    for (int i = 0; i < N; i++)
    {
        forks[i] = makeFork(i);
        philosophers[i] = makePhilosopher(i);
    }

    for (int i = 0; i < N; i++) pthread_create(&philosophers[i].thread, NULL, philosophize, (void *) &philosophers[i].id);
    for (int i = 0; i < N; i++) pthread_join(philosophers[i].thread, NULL);

    return 0;
}