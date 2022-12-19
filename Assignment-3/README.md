# Assignment-3

## Problem 1

Problem 1 has two sub-problems, each being a version of the famous Dining Philosophers Problem. The solutions to each are in directories `1/a` and `1/b` respectively. Following is the structure of the directory `./1`:

```bash
1
├── a
│   ├── order.c
│   └── sem.c
├── b
│   └── main.c
├── helper.h
└── README.md
```

## Problem 2

Problem 2 has three sub-problems that require the implementation of inter-process communication. The solutions to each are in directories `2/fifo`, `2/shm`, and `2/sockets` respectively. Following is the structure of the directory `./2`:

```bash
2
├── fifo
│   ├── client.c
│   └── server.c
├── shm
│   ├── client.c
│   └── server.c
├── sockets
│   ├── client.c
│   └── server.c
├── helper.h
├── run.c
└── README.md
```

## Problem 3

## Resources and References

### Problem 1

#### a

- [Manual Page: `sem_wait()`](https://man7.org/linux/man-pages/man3/sem_timedwait.3.html)
- [Manual Page: `sem_post()`](https://man7.org/linux/man-pages/man3/sem_post.3.html)

#### b
- [Manual Page: `sem_trywait()`](https://man7.org/linux/man-pages/man3/sem_timedwait.3.html)

### Problem 2

[**CSE231** Lecture Slides: *Dr Sambuddho Chakravarty*](https://drive.google.com/file/d/1Rb3mEzsDxChImM1L72_5yoOQ6acMSByi/view)

#### sockets

- [Manual Page: `socket()`](https://man7.org/linux/man-pages/man2/socket.2.html)
- [Manual Page: `connect()`](https://man7.org/linux/man-pages/man2/connect.2.html)
- [Manual Page: `bind()`](https://man7.org/linux/man-pages/man2/bind.2.html)
- [Manual Page: `accept()`](https://man7.org/linux/man-pages/man2/accept.2.html)
- [Manual Page: `listen()`](https://man7.org/linux/man-pages/man2/listen.2.html)

#### fifo
- [Manual Page: `mkfifo()`](https://man7.org/linux/man-pages/man3/mkfifo.3.html)

#### shm
- [Manual Page: `ftok()`](https://man7.org/linux/man-pages/man3/ftok.3.html)
- [Manual Page: `shmget()`](https://man7.org/linux/man-pages/man2/shmget.2.html)
- [Manual Page: `shmat()`](https://man7.org/linux/man-pages/man3/shmat.3p.html)
- [Manual Page: `shmdt()`](https://man7.org/linux/man-pages/man3/shmdt.3p.html)
- [Manual Page: `shmctl()`](https://man7.org/linux/man-pages/man2/shmctl.2.html)

### Problem 3
