# Dining Philosophers Problem

The Dining Philosophers Problem is a classic problem in concurrency theory. Following is its set up:

- A group of philosophers are seated around a round table eating spaghetti
- A philosopher can do only two things: eat or think
- Each philosopher has a bowl in front of them, and a fork to their left and right
- A philosopher can only eat if they have both forks
- If a philosopher does not have both forks, they must wait until they do
- A fork can be used by only one philosopher at a time

The challenge is to design a program such that no philosopher starves.

## Classic Problem

The classic problem follows the set up as described above. Note that if each philosopher picks up the forks in the same order, then a deadlock can occur. This is because each philosopher may wait for the fork to their left, which is being held by the philosopher to their left; a case of circular wait.

### Solution

One solution is to order the fork-picking "request" of the philosophers. Assign each philosopher an index. If the philosopher's index is:

- EVEN: pick up the forks in the order first LEFT, then RIGHT
- ODD: pick up the forks in the order first RIGHT, then LEFT

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

## Modified Problem

The modified problem follows a similar set up. However, the philosophers now eat spaghetti with sauce.

- There are two sauce bowls in the middle of the table
- A philosopher can only eat if they have both forks and one sauce bowl
- A philosopher can use any sauce bowl at any point of time
- A sauce bowl can be used by only one philosopher at a time

### Solution

One solution is to check which sauce bowl is unoccupied (if any) before trying to use it. Note that the philosophers pick up the forks in the same order as in the classic problem.

This is seen in code in `b/mutex.c` and `b/semaphore.c` as follows:

```c
int chooseBowl()
{
    if (try_access(&bowls[0].type) == 0) return 0;
    else {
        access(&bowls[1].lock);
        return 1;
    }
}
```

Depending on the implementation, the `access` and `try_access` functions can be:

- `access`: `pthread_mutex_lock` or `sem_wait`
- `try_access`: `pthread_mutex_trylock` or `sem_trywait`

This way, no bowl will remain unoccupied, hence maximizing efficiency. In the worst case, each bowl can have two philosophers waiting to use it.

##  Implementations/Variants of the Solution

In implementation, the Philosophers are simulated using POSIX threads `pthread_t`.

- Variant 1: Using Mutex locks `pthread_mutex_t` for Forks and Sauce Bowls
- Variant 2: Using Semaphores `sem_t` for Forks and Sauce Bowls

## Run

To compile the programs, use the following command:

```bash
make 1a 1b
```

To run a program, use the following command:

```bash
make run1<variant><method>
```

where `<variant>` is either `a` or `b` and `<method>` is either `m` or `s`.