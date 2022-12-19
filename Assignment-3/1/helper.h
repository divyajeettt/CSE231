#include <semaphore.h>

#define N 5
#define LEFT i
#define RIGHT (i+1) % N
#define FIRST (i%2 == 0) ? LEFT : RIGHT
#define SECOND (i%2 == 0) ? RIGHT : LEFT


struct Request
{
    struct Philosopher *philosopher;
    struct Request *next;
};

struct Queue
{
    int length;
    struct Request *head;
    struct Request *tail;
};

struct Philosopher
{
    int id;
    long long eaten;
    pthread_t thread;
};

struct Fork { sem_t semaphore; };

struct SauceBowl { sem_t semaphore; };


struct Request makeRequest(struct Philosopher *philosopher)
{
    struct Request request = { philosopher, NULL };
    return request;
}


struct Queue makeQueue()
{
    struct Queue queue = { 0, NULL, NULL };
    return queue;
}


void enqueue(struct Queue *queue, struct Request *request)
{
    if (queue->length == 0) queue->head = request;
    else queue->tail->next = request;
    queue->tail = request;
    queue->length++;
}


 void dequeue(struct Queue *queue)
{
    queue->head = queue->head->next;
    queue->length--;
}


struct Philosopher makePhilosopher(int id)
{
    pthread_t tid;
    struct Philosopher philosopher = { id, 0ll, tid };
    return philosopher;
}


struct Fork makeFork()
{
    sem_t semaphore;
    if (sem_init(&semaphore, 0, 1) != 0)
    {
        perror("makeFork() sem_init");
        exit(EXIT_FAILURE);
    }

    struct Fork fork = { semaphore };
    return fork;
}


struct SauceBowl makeSauceBowl()
{
    sem_t semaphore;
    if (sem_init(&semaphore, 0, 1) != 0)
    {
        perror("makeSauceBowl() sem_init");
        exit(EXIT_FAILURE);
    }

    struct SauceBowl sauceBowl = { semaphore };
    return sauceBowl;
}


void think(struct Philosopher *philosopher)
{
    printf("Philosopher %d: THINKING \n", philosopher->id);
    usleep(1e6);
}


void eat(struct Philosopher *philosopher)
{
    printf("Philosopher %d: EATING [total: %lld times] \n", philosopher->id, ++philosopher->eaten);
    usleep(1e6);
}