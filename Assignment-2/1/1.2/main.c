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
    double timeA, timeB, timeC;

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
        nice(-1);
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
            param.sched_priority = 10;
            sched_setscheduler(pid2, SCHED_RR, &param);
            if (execlp("bash", "bash", "./1/1.2/buildB.sh", (char *) NULL) == -1)
            {
                perror("execlp");
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
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
                param.sched_priority = 99;
                sched_setscheduler(pid3, SCHED_FIFO, &param);
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
            else
            {
                waitpid(pid3, NULL, 0);
                clock_gettime(CLOCK_REALTIME, &endC);

                timeC = (endC.tv_sec - startC.tv_sec) + (endC.tv_nsec - startC.tv_nsec) / 1000000000.0;
                writeToFile(file, "C", timeC);
                printf("Time taken by 3rd Process (SCHED_FIFO): %lf seconds \n", timeC);
            }
            waitpid(pid2, NULL, 0);
            clock_gettime(CLOCK_REALTIME, &endB);

            timeB = (endB.tv_sec - startB.tv_sec) + (endB.tv_nsec - startB.tv_nsec) / 1000000000.0;
            writeToFile(file, "B", timeB);
            printf("Time taken by 2nd Process (SCHED_RR): %lf seconds \n", timeB);
        }
        waitpid(pid1, NULL, 0);
        clock_gettime(CLOCK_REALTIME, &endA);

        timeA = (endA.tv_sec - startA.tv_sec) + (endA.tv_nsec - startA.tv_nsec) / 1000000000.0;
        writeToFile(file, "A", timeA);
        printf("Time taken by 1st Process (SHCED_OTHER): %lf seconds \n", timeA);
    }

    fprintf(file, "\n");
    fclose(file);

    return 0;
}