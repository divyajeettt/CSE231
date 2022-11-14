#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    struct timespec start, end;
    double time;

    clock_gettime(CLOCK_REALTIME, &start);
    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process
        if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
        {
            perror("execl");
            return 1;
        }
        return 0;
    }
    waitpid(pid1, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken by 1st Process: %f seconds \n", time);

    clock_gettime(CLOCK_REALTIME, &start);
    int pid2 = fork();
    if (pid2 == 0)
    {
        // Child process
        if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
        {
            perror("execl");
            return 1;
        }
        return 0;
    }
    waitpid(pid2, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken by 2nd Process: %f seconds \n", time);

    clock_gettime(CLOCK_REALTIME, &start);
    int pid3 = fork();
    if (pid3 == 0)
    {
        // Child process
        if (execl("bash", "./1/1.2/build.sh", NULL) == -1)
        {
            perror("execl");
            return 1;
        }
        return 0;
    }
    waitpid(pid3, NULL, 0);
    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken by 3rd Process: %f seconds \n", time);

    return 0;
}