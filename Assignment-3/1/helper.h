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

struct Fork {
    int id;
    sem_t semaphore;
};

struct SauceBowl {
    int id;
    sem_t semaphore;
};


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


struct Fork makeFork(int id)
{
    sem_t semaphore;
    if (sem_init(&semaphore, 0, 1) != 0)
    {
        perror("makeFork() sem_init");
        exit(EXIT_FAILURE);
    }

    struct Fork fork = { id, semaphore };
    return fork;
}


struct SauceBowl makeSauceBowl(int id)
{
    sem_t semaphore;
    if (sem_init(&semaphore, 0, 1) != 0)
    {
        perror("makeSauceBowl() sem_init");
        exit(EXIT_FAILURE);
    }

    struct SauceBowl sauceBowl = { id, semaphore };
    return sauceBowl;
}


void think(struct Philosopher *philosopher)
{
    printf("Philosopher %d: THINKING \n", philosopher->id);
    usleep(1e6);
}


void eat(struct Philosopher *philosopher, struct Fork fork1, struct Fork fork2, struct SauceBowl *bowl)
{
    if (bowl == NULL) printf(
        "Philosopher %d: EATING [forks: %d & %d; total: %lld times] \n", philosopher->id, fork1.id, fork2.id, ++philosopher->eaten
    );
    else printf(
        "Philosopher %d: EATING [forks: %d & %d; bowl: %d; total: %lld times] \n", philosopher->id, fork1.id, fork2.id, bowl->id, ++philosopher->eaten
    );
    usleep(1e6);
}