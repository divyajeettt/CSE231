#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

typedef long long ll;

///////////////////////////////////////////////////////////////////////////////////////////////////

void countA()
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

void countB()
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

void countC()
{
    for (ll count=1; count < 1+pow(2, 32); count++);
}

void *count(void *arg)
{
    countA();
    countB();
    countC();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, &count, NULL);
    // set threadA to run on CPU 0
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(threadA, sizeof(cpu_set_t), &cpuset);

    pthread_create(&threadB, NULL, &count, NULL);
    // set threadB to run on CPU 1
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(threadB, sizeof(cpu_set_t), &cpuset);

    pthread_create(&threadC, NULL, &count, NULL);
    // set threadC to run on CPU 2
    CPU_ZERO(&cpuset);
    CPU_SET(2, &cpuset);
    pthread_setaffinity_np(threadC, sizeof(cpu_set_t), &cpuset);

    clock_t start = clock();

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    clock_t end = clock();

    printf("Time taken: %f seconds", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}