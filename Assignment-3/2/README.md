# Inter-process Communication

The sub-problems in this problem require us to set up an IPC between two processes, `P1` and `P2`, using three different mechanisms.

The processes should perform the following tasks without failure:

- `P1` should generate an array of 50 random strings, each of a fixed length
- `P1` should send a collection of 5 strings to `P2` at a time using the selected IPC mechanism, along with the highest ID of the strings
- `P2` should receive the strings, print them to the terminal
- `P2` should send back to `P1` the highest ID of the strings it received
- `P1` should acknowledge the receipt of the highest ID, and continue sending the strings till the array is exhausted

The only difference between the three sub-problems is the IPC mechanism used to send the strings. By convention:

- `*/server.c` corresponds to the process `P1`
- `*/client.c` corresponds to the process `P2`

## FIFOs

Solutions are in the `fifo` directory.

## Shared Memory

Solutions are in the `shm` directory.

## Sockets

Solutions are in the `sockets` directory.

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

***NOTE**: The client program must be executed **AFTER** the server program.*