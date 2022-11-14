#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // print current working directory
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s \n", cwd);

    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process
        if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
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
            if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
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
                if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
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
                printf("Time taken by 3rd Process: %f seconds \n", time);
            }

            struct timespec start, end;
            clock_gettime(CLOCK_REALTIME, &start);
            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &end);
            double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            printf("Time taken by 2nd Process: %f seconds \n", time);
        }

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);
        wait(NULL);
        clock_gettime(CLOCK_REALTIME, &end);
        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Time taken by 1st Process: %f seconds \n", time);
    }

    return 0;
}