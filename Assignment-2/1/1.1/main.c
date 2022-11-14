#include <math.h>
#include <time.h>
#include <stdio.h>
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

///////////////////////////////////////////////////////////////////////////////////////////////////

void *Thr_A(void *arg)
{
    struct sched_param param;
    param.sched_priority = 0;
    if (pthread_setschedparam(pthread_self(), SCHED_OTHER, &param) != 0)
    {
        perror("pthread_setschedparam");
        pthread_exit(NULL);
    }
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    countB();
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Thread A: %lf seconds \n", time);
    return NULL;
}

void *Thr_B(void *arg)
{
    struct sched_param param;
    param.sched_priority = 1;
    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0)
    {
        perror("pthread_setschedparam");
        pthread_exit(NULL);
    }
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    countB();
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Thread B: %lf seconds \n", time);
    return NULL;
}

void *Thr_C(void *arg)
{
    struct sched_param param;
    param.sched_priority = 1;
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0)
    {
        perror("pthread_setschedparam");
        pthread_exit(NULL);
    }
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    countB();
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Thread C: %lf seconds \n", time);
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, &Thr_A, NULL);
    pthread_create(&threadB, NULL, &Thr_B, NULL);
    pthread_create(&threadC, NULL, &Thr_C, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    return 0;
}