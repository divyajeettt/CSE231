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

    struct timespec startA, endA, startB, endB, startC, endC;
    double time;

    struct sched_param param;

    clock_gettime(CLOCK_REALTIME, &startA);
    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork1");
        return 1;
    }
    else if (pid1 == 0)
    {
        // Child process
        if (execlp("bash", "bash", "./1/1.2/buildA.sh", (char *) NULL) == -1)
        {
            perror("execlp1");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        param.sched_priority = 5;
        sched_setscheduler(pid1, SCHED_OTHER, &param);

        clock_gettime(CLOCK_REALTIME, &startB);
        int pid2 = fork();
        if (pid2 < 0)
        {
            perror("fork2");
            return 1;
        }
        else if (pid2 == 0)
        {
            // Child process
            if (execlp("bash", "bash", "./1/1.2/buildB.sh", (char *) NULL) == -1)
            {
                perror("execlp");
                return 1;
            }
            else {
                return 0;
            }
        }
        else
        {
            param.sched_priority = 20;
            sched_setscheduler(pid1, SCHED_RR, &param);

            clock_gettime(CLOCK_REALTIME, &startC);
            int pid3 = fork();
            if (pid3 < 0)
            {
                perror("fork3");
                return 1;
            }
            else if (pid3 == 0)
            {
                // Child process
                if (execlp("bash", "bash", "./1/1.2/buildC.sh", (char *) NULL) == -1)
                {
                    perror("execlp");
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else {
                param.sched_priority = 30;
                sched_setscheduler(pid1, SCHED_FIFO, &param);
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &endC);
            }
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &endB);
        }
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &endA);
    }

    time = (endA.tv_sec - startA.tv_sec) + (endA.tv_nsec - startA.tv_nsec) / 1000000000.0;
    writeToFile(file, "A", time);
    printf("Time taken by 1st Process: %f seconds \n", time);

    time = (endB.tv_sec - startB.tv_sec) + (endB.tv_nsec - startB.tv_nsec) / 1000000000.0;
    writeToFile(file, "B", time);
    printf("Time taken by 2nd Process: %f seconds \n", time);

    time = (endC.tv_sec - startC.tv_sec) + (endC.tv_nsec - startC.tv_nsec) / 1000000000.0;
    writeToFile(file, "C", time);
    printf("Time taken by 3rd Process: %f seconds \n", time);

    fprintf(file, "\n");
    fclose(file);

    return 0;
}