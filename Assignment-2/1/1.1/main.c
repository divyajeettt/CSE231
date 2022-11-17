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

void writeToFile(FILE *file, char *str, double time)
{
    char buffer[100];
    sprintf(buffer, "%f", time);

    fprintf(file, str);
    fprintf(file, "\t");
    fprintf(file, buffer);
    fprintf(file, "\t");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void *Thr_A(void *arg)
{
    FILE *file = (FILE *) arg;

    struct sched_param param;
    param.sched_priority = 0;
    if (pthread_setschedparam(pthread_self(), SCHED_OTHER, &param) != 0)
    {
        perror("pthread_setschedparam (Thr-A)");
        pthread_exit(NULL);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &end);

    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "A", time);
    printf("Thread A: %lf seconds \n", time);

    return NULL;
}

void *Thr_B(void *arg)
{
    FILE *file = (FILE *) arg;

    struct sched_param param;
    param.sched_priority = 1;
    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0)
    {
        perror("pthread_setschedparam (Thr-B)");
        pthread_exit(NULL);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &end);

    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "B", time);
    printf("Thread B: %lf seconds \n", time);

    return NULL;
}

void *Thr_C(void *arg)
{
    FILE *file = (FILE *) arg;

    struct sched_param param;
    param.sched_priority = 1;
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0)
    {
        perror("pthread_setschedparam (Thr-C)");
        pthread_exit(NULL);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &end);

    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "C", time);
    printf("Thread C: %lf seconds \n", time);

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    FILE *file = fopen("./1/1.1/benchmark.csv", "a");

    pthread_t threadA, threadB, threadC;

    pthread_create(&threadA, NULL, &Thr_A, file);
    pthread_create(&threadB, NULL, &Thr_B, file);
    pthread_create(&threadC, NULL, &Thr_C, file);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    fprintf(file, "\n");
    fclose(file);

    return 0;
}