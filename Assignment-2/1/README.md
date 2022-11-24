# Linux `pthread` and process scheduling

## Thread Scheduling

File `1/1.1/main.c` contains a program that creates 3 threads, each of which count from 1 to 2³² and time their own execution. The compiled program run using `sudo` permissions.

The threads are created using `pthread_create()` and the scheduling policy is set using `pthread_setschedparam()`. The thread priorities are also changed. The three threads use the following scheduling policies:

- `Thr-A`: `SCHED_OTHER`
- `Thr-B`: `SCHED_RR`
- `Thr-C`: `SCHED_FIFO`

The program was run on a machine with 1, 2, and 4 cores. The results were recorded in a csv file, and plotted using python. The X-Axis of the plots show the thread-priorities, and the Y-Axis shows the time taken to complete the threads.

## Process Scheduling

File `1/1.2/main.c` contains a program that creates 3 processes, each of which creates a copy of the preprocessed `/linux-5.19.8` directory and compiles it (*see Footnotes*). The process are executed parallely. The compiled program run using `sudo` permissions.

The child processes are created using `fork()` thrice. The processes threads use the following scheduling policies:

- `Pr-A`: `SCHED_OTHER`
- `Pr-B`: `SCHED_RR`
- `Pr-C`: `SCHED_FIFO`

The results were recorded in a csv file, and plotted using python. The X-Axis of the plots show the process-priorities, and the Y-Axis shows the time taken to complete the processes.

## Footnotes

The compilation being done in Problem 1.2 only creates the `bzImage` of the preprocessed kernel using the following command:

```bash
make bzImage
```