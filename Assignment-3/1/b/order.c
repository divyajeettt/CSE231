#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../helper.h"


struct Philosopher philosophers[N];
struct Queue requests;


void *philosophize(void *arg)
{
    int i = *((int *) arg);
    struct Request request = makeRequest(&philosophers[i]);
    while (1)
    {
        enqueue(&requests, &request);
        think(&philosophers[i]);

        while (requests.head != &request);
        eat(&philosophers[i]);
        dequeue(&requests);
    }
}


int main()
{
    requests = makeQueue();
    for (int i = 0; i < N; i++)
    {
        philosophers[i] = makePhilosopher(i);
        pthread_create(&philosophers[i].thread, NULL, philosophize, (void *) &philosophers[i].id);
    }

    for (int i = 0; i < N; i++) pthread_join(philosophers[i].thread, NULL);

    return 0;
}