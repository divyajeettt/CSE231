# Assignment-3

## Problem 1

Problem 1 has two sub-problems, 1.1 and 1.2, requiring us to implement thread-scheduling and process-scheduling respectively. The solutions to each are in directories `1/1.1` and `1/1.2` respectively. Following is the structure of the directory `./1`:

```bash
1
├── 1.1
│   ├── Benchmarks
│   │   ├── Assets
│   │   │   ├── Dualcore
│   │   │   │   └── *.png
│   │   │   ├── Quadcore
│   │   │   │   └── *.png
│   │   │   ├── Unicore
│   │   │   │   └── *.png
│   │   │   └── *.png
│   │   └── plotter.py
│   └── main.c
├── 1.2
│   ├── Benchmarks
│   │   ├── Assets
│   │   │   ├── Dualcore
│   │   │   │   └── *.png
│   │   │   ├── Quadcore
│   │   │   │   └── *.png
│   │   └── plotter.py
│   ├── .config
│   ├── buildA.sh
│   ├── buildB.sh
│   ├── buildC.sh
│   └── main.c
└── README.md
```

## Problem 2

Problem 2 required us to write a system call that copies one 2-dimensional floating point matrix to another, and patch it. The solution is in the directory `./2`. Following is the structure of the directory `./2`:

```bash
2
├── diff.patch
├── test.c
└── README.md
```

## Resources and References

### Problem 1

#### 1.1

- [Manual Page: `pthread_setschedparam()`](https://man7.org/linux/man-pages/man3/pthread_setschedparam.3.html)
- [Manual Page: `nice()`](https://man7.org/linux/man-pages/man2/nice.2.html)

#### 1.2

- [Manual Page: `sched_setscheduler()`](https://man7.org/linux/man-pages/man2/sched_setscheduler.2.html)
- [Manual Page: `nice()`](https://man7.org/linux/man-pages/man2/nice.2.html)

### Problem 2

- [Tutorial: How to write a System Call in C (Linux)](https://brennan.io/2016/11/14/kernel-dev-ep3/)
