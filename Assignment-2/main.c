#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

typedef long long ll;

///////////////////////////////////////////////////////////////////////////////////////////////////

void *countA(void *arg)
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

void *countB(void *arg)
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

void *countC(void *arg)
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

pthread_t *createThreads()
{
    pthread_t *threads = (pthread_t *) malloc(3*sizeof(pthread_t));
    pthread_create(&threads[0], NULL, &countA, NULL);
    pthread_create(&threads[1], NULL, &countB, NULL);
    pthread_create(&threads[2], NULL, &countC, NULL);
    return threads;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

double scheduleThreads(int policy, pthread_t *threads, int n)
{
    for (int i=0; i < n; i++)
    {
        struct sched_param param;
        param.sched_priority = 40 * i;
        pthread_setschedparam(threads[i], policy, &param);
    }

    clock_t start = clock();

    // alternate between threads for 1 second
    for (int i=0; i < 1000; i++)
    {
        for (int j=0; j < n; j++)
        {
            pthread_kill(threads[j], SIGCONT);
            usleep(1000);
            pthread_kill(threads[j], SIGSTOP);
        }
    }

    // for (int i=0; i < n; i++)
    // {
    //     pthread_join(threads[i], NULL);
    // }
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("SCHED_OTHER: %f seconds \n", scheduleThreads(SCHED_OTHER, createThreads(), 3));
    printf("SCHED_RR: %f seconds \n", scheduleThreads(SCHED_RR, createThreads(), 3));
    printf("SCHED_FIFO: %f seconds \n", scheduleThreads(SCHED_FIFO, createThreads(), 3));

    return 0;
}