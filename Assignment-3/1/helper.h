#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define LEFT i
#define RIGHT (i+1) % N


struct Philospher
{
    long long eaten;
    pthread_t thread;
    pthread_cond_t cond;
};


struct Fork
{
    sem_t semaphore;
    pthread_mutex_t lock;
    struct Philospher *owner;
};


struct SauceBowl
{
    pthread_mutex_t lock;
    struct Philospher *owner;
};


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

    sem_t semaphore;
    if (sem_init(&semaphore, 0, 1) != 0)
    {
        printf("Semaphore init failed \n");
        exit(EXIT_FAILURE);
    }

    struct Fork fork = { semaphore, lock, NULL };
    return fork;
}


struct SauceBowl makeSauceBowl()
{
    pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed \n");
        exit(EXIT_FAILURE);
    }

    struct SauceBowl sauceBowl = { lock, NULL };
    return sauceBowl;
}