# Dining Philosophers Problem

The Dining Philosophers Problem is a classic problem in concurrency theory. Following is its set up:

- A group of philosophers are seated around a round table eating spaghetti
- A philosopher can do only two things: eat or think
- Each philosopher has a bowl in front of them, and a fork to their left and right
- A philosopher can only eat if they have both forks
- If a philosopher does not have both forks, they must wait until they do
- A fork can be used by only one philosopher at a time

The challenge is to design a program such that no philosopher starves.

## (a) Classic Problem

The classic problem follows the set up as described above. Note that if each philosopher picks up the forks in the same order, then a deadlock can occur. This is because each philosopher may wait for the fork to their left, which is being held by the philosopher to their left; a case of circular wait.

### Solution 1 (Strict Alternation of Resource Requests)

One solution is to enforce a strict alternation of resource requests. This ensures that only one philosopher can gain access to resources and eat at a time.

A queue of requests is maintained during the program runtime. A philosopher who wishes to eat adds their request to the queue and waits for their turn. A philosopher who has eaten removes their request from the queue.

This prevents a deadlock because no matter what order the requests are in, only one philosopher will be able to eat at a time. This is achieved as a philosopher busy waits for their turn. This is seen in code in `a/order.c` as follows

```c
while (requests.head != &request);
```

This approach is not as efficient, because only one philosopher will be able to eat at a time. There is also a lot of overhead involved in alternation. This method is as good as using a [turn variable](https://www.gatevidyalay.com/tag/turn-variable-in-os/) that alternated between 0, 1, 2, ..., N-1.

### Solution 2 (Utilizing Semaphores)

Another solution is to order the way in which philosophers pick up their forks. Assign each philosopher an index. If the philosopher's index is:

- **EVEN**: pick up the forks in the order first LEFT, then RIGHT
- **ODD**: pick up the forks in the order first RIGHT, then LEFT

This ensures that a circular wait (which leads to a deadlock) cannot occur. This is seen in code in `helper.h` as follows:

```c
#define N 5
#define LEFT i
#define RIGHT (i+1) % N
#define FIRST (i%2 == 0) ? LEFT : RIGHT
#define SECOND (i%2 == 0) ? RIGHT : LEFT
```

Here, `i` is the index of the philospher, which is:

```c
int i = *((int *) ((void *) &philosopher->id));
```

Here, forks are simulated using semaphores `sem_t`. In both variants of the code, the philosophers are simulated using POSIX threads `pthread_t`.

## (b) Modified Problem

The modified problem follows a similar set up. However, the philosophers now eat spaghetti with sauce.

- There are two sauce bowls in the middle of the table
- A philosopher can only eat if they have both forks and one sauce bowl
- A philosopher can use any sauce bowl at any point of time
- A sauce bowl can be used by only one philosopher at a time

### Solution

One solution is to check which sauce bowl is unoccupied (if any) before trying to use it. Note that the philosophers pick up the forks in the same order as in the classic problem.

This is seen in code in `b/main.c` as follows:

```c
int chooseBowl()
{
    if (sem_trywait(&bowls[0].semaphore) == 0) return 0;
    else {
        sem_wait(&bowls[1].semaphore);
        return 1;
    }
}
```

This way, no bowl will remain unoccupied, hence maximizing efficiency. In the worst case, each bowl can have two philosophers waiting to use it.

Here, the sauce bowls are simulated using semaphores `sem_t`.


## Run

To compile the programs, use the following command:

```bash
make make1
```

To run a program, use the following command:

```bash
make run1<variant>
```

and `<variant>` is either `order`, `sem`, or `mod`, to run `a/order`, `a/sem`, or `b/main` respectively.