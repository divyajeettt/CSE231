#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process
        if (execl("bash", "./build.sh", NULL) != -1)
        {
            perror("execl");
        }
    }
    else
    {
        // Parent process
        int pid2 = fork();
        if (pid2 == 0)
        {
            // Child process
            if (execl("bash", "./build.sh", NULL) != -1)
            {
                perror("execl");
            }
        }
        else
        {
            // Parent process
            int pid3 = fork();
            if (pid3 == 0)
            {
                // Child process
                if (execl("bash", "./build.sh", NULL) != -1)
                {
                    perror("execl");
                }
            }
            else {
                struct timespec start, end;
                clock_gettime(CLOCK_REALTIME, &start);
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &end);
                double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
                printf("Time taken by 3rd Process is : %f seconds \n", time);
            }

            struct timespec start, end;
            clock_gettime(CLOCK_REALTIME, &start);
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &end);
            double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            printf("Time taken by 2nd Process is : %f seconds \n", time);
        }

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Time taken by 1st Process is : %f seconds \n", time);
    }

    return 0;
}