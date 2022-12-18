# Inter-process Communication

The sub-problems in this problem require us to set up an IPC between two processes, `P1` and `P2`, using three different mechanisms. The processes should perform the following tasks without failure:

- `P1` should generate an array of 50 random strings, each of a fixed length
- `P1` should send a collection of 5 strings to `P2` at a time using the selected IPC mechanism, along with the highest ID of the strings
- `P2` should receive the strings and print them to the terminal
- `P2` must send back to `P1` the highest ID of the strings it received
- `P1` must acknowledge the receipt of the highest ID and continue sending the strings till the array is exhausted

The only difference between the three sub-problems is the IPC mechanism used to send the strings. By convention:

- `*/server.c` corresponds to the process `P1`
- `*/client.c` corresponds to the process `P2`


## Sockets

Solutions are in the `sockets` directory. The UNIX Domain sockets use `SOCK_STREAM` as the socket type.

## Shared Memory

Solutions are in the `shm` directory. To ensure that the `P2` writes the highest ID it received into the memory before `P1` reads it, `P1` busy waits as follows

```c
while (strlen(buffer) != LENGTH);
```

while `P2` busy waits as follows to ensure that the next batch of strings is written into the memory before it reads them again

```c
while (strlen(shm) == LENGTH);
```

Note

## FIFOs

Solutions are in the `fifo` directory. The solutin uses two FIFOs, one for each direction of communication. To ensure that `P1` doesn't close the FIFOs prematurely, it makes use of halt commands as follows

```c
usleep(1e3);
```

for each message sent.

## Run

To compile the programs, use the following command:

```bash
make <variant>
```

To run the programs on a common terminal, use either one of the following command:

```bash
make run2<variant>
```

OR

```bash
./2/run <variant>
```

To run the programs on two separate terminals, use the following two commands on two separate terminals:

```bash
./2/<variant>/server
./2/<variant>/client
```

where `<variant>` is either `fifo`, `shm`, or `sockets`.

***NOTE**: The client program must be executed **AFTER** the server program, as the server initiates the communication.*