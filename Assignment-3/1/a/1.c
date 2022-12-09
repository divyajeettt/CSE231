#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 5
#define LEFT (i+N-1) % N
#define RIGHT (i+1) % N
#define THINKING 0
#define EATING 1


struct Philospher
{
    long long eaten;
    pthread_t thread;
    pthread_cond_t cond;
};


struct Fork
{
    pthread_mutex_t lock;
    struct Philospher *owner;
};


struct Philospher philosophers[N];
struct Fork forks[N];


struct Philospher makePhilosopher()
{
    pthread_t tid;
    pthread_cond_t cond;
    if (pthread_cond_init(&cond, NULL) != 0)
    {
        printf("Cond init failed \n");
        exit(EXIT_FAILURE);
    }

    struct Philospher philosopher = { 0ll, tid, cond };
    return philosopher;
}


struct Fork makeFork()
{
    pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed \n");
        exit(EXIT_FAILURE);
    }

    struct Fork fork = { lock, NULL };
    return fork;
}


void *eat(void *arg)
{
    int i = *((int *) arg);

    pthread_mutex_lock(&forks[LEFT].lock);
    pthread_mutex_lock(&forks[RIGHT].lock);

    if (forks[LEFT].owner == NULL && forks[RIGHT].owner == NULL)
    {
        forks[LEFT].owner = &philosophers[i];
        forks[RIGHT].owner = &philosophers[i];
        philosophers[i].eaten++;
        pthread_cond_signal(&philosophers[i].cond);
    }
    else
    {
        pthread_cond_wait(&philosophers[i].cond, &forks[LEFT].lock);
        pthread_cond_wait(&philosophers[i].cond, &forks[RIGHT].lock);
    }

    forks[LEFT].owner = NULL;
    forks[RIGHT].owner = NULL;

    pthread_mutex_unlock(&forks[LEFT].lock);
    pthread_mutex_unlock(&forks[RIGHT].lock);
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
        int *arg = (int *) malloc(sizeof(int));
        for (int i = 0; i < N; i++)
        {
            *arg = i;
            pthread_create(&philosophers[i].thread, NULL, eat, arg);
        }
        for (int i = 0; i < N; i++)
        {
            pthread_join(philosophers[i].thread, NULL);
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("Philosopher %d: Eaten %lld times \n", i, philosophers[i].eaten);
    }

    return 0;
}