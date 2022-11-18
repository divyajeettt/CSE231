#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

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

int main()
{
    FILE *file = fopen("./1/1.2/Benchmarks/benchmark.csv", "a");

    struct timespec start, end;
    double time;

    struct sched_param param;

    clock_gettime(CLOCK_REALTIME, &start);
    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process
        if (execlp("bash", "bash", "./1/1.2/buildA.sh", (char *) NULL) == -1)
        {
            perror("execlp");
            return 1;
        }
        return 0;
    }
    param.sched_priority = 99;
    sched_setscheduler(pid1, SCHED_OTHER, &param);

    waitpid(pid1, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);

    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "A", time);
    printf("Time taken by 1st Process: %f seconds \n", time);

    clock_gettime(CLOCK_REALTIME, &start);
    int pid2 = fork();
    if (pid2 == 0)
    {
        // Child process
        if (execlp("bash", "bash", "./1/1.2/buildB.sh", (char *) NULL) == -1)
        {
            perror("execlp");
            return 1;
        }
        return 0;
    }
    param.sched_priority = 99;
    sched_setscheduler(pid1, SCHED_RR, &param);

    waitpid(pid2, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);

    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "B", time);
    printf("Time taken by 2nd Process: %f seconds \n", time);

    clock_gettime(CLOCK_REALTIME, &start);
    int pid3 = fork();
    if (pid3 == 0)
    {
        // Child process
        if (execlp("bash", "bash", "./1/1.2/buildC.sh", (char *) NULL) == -1)
        {
            perror("execlp");
            return 1;
        }
        return 0;
    }
    param.sched_priority = 99;
    sched_setscheduler(pid1, SCHED_FIFO, &param);

    waitpid(pid3, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    writeToFile(file, "C", time);
    printf("Time taken by 3rd Process: %f seconds \n", time);

    fprintf(file, "\n");
    fclose(file);

    return 0;
}