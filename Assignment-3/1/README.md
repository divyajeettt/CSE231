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

- EVEN: pick up the forks in the order LEFT-RIGHT
- ODD: pick up the forks in the order RIGHT-LEFT

This ensures that a circular wait (which leads to a deadlock) cannot occur. This is seen in code in `helper.h` as follows:

```c
#define N 5
#define LEFT i
#define RIGHT (i+1) % N
#define FIRST (i%2 == 0) ? LEFT : RIGHT
#define SECOND (i%2 == 0) ? RIGHT : LEFT
```

## Modified Problem

The modified problem follows a similar set up. However, the philosophers now eat spaghetti with sauce.

- There are two sauce bowls in the middle of the table
- A philosopher can only eat if they have both forks and one sauce bowl
- A philosopher can use any sauce bowl at any point of time
- A sauce bowl can be used by only one philosopher at a time

### Solution

One solution is as follows. Assume the (already indexed) philosopher thinks of a binary digit while thinking. Follow:

- If the digit is 0, use the first sauce bowl
- If the digit is 1, use the second sauce bowl

Note that the philosophers pick up the forks in the same order as in the classic problem. This is seen in code in `helper.h` as follows:

```c
int think(struct Philosopher *philosopher)
{
    printf("Philosopher %d: THINKING \n", philosopher->id);
    usleep(1e6);
    return (rand() % 2);
}
```

This works because each philosopher randomly decides which bowl to use. Even if all philosophers choose the same bowl, as at least one philosopher will be able to eat due to the order of picking up the forks.

##  Implementations/Variants of the Solution

In implementation, the Philosophers are simulated using POSIX threads (`pthread_t` as provided by the `pthread` library).

- Variant 1: Using Mutex locks (`pthread_mutex_t`) for Forks and Sauce Bowls
- Variant 2: Using Semaphores (`sem_t`) for Forks and Sauce Bowls

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