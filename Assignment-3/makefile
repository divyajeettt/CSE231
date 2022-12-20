all: make1 make2 make3

make1: 1a 1b
make2: fifo shm sockets
make3: module

clean: clean1 clean2 clean3

1a:
	gcc -pthread -o 1/a/order 1/a/order.c
	gcc -pthread -o 1/a/sem 1/a/sem.c

1b:
	gcc -pthread -o 1/b/order 1/b/order.c
	gcc -pthread -o 1/b/sem 1/b/sem.c

fifo:
	gcc -o 2/run 2/run.c
	gcc -o 2/fifo/client 2/fifo/client.c
	gcc -o 2/fifo/server 2/fifo/server.c

shm:
	gcc -o 2/run 2/run.c
	gcc -o 2/shm/client 2/shm/client.c
	gcc -o 2/shm/server 2/shm/server.c

sockets:
	gcc -o 2/run 2/run.c
	gcc -o 2/sockets/client 2/sockets/client.c
	gcc -o 2/sockets/server 2/sockets/server.c

module:
	cd 3 && make

run1ao:
	./1/a/order
run1as:
	./1/a/sem
run1bo:
	./1/b/order
run1bs:
	./1/b/sem

run2fifo:
	./2/run fifo
run2shm:
	./2/run shm
run2sockets:
	./2/run sockets

clean1:
	rm -f 1/a/order 1/a/sem
	rm -f 1/b/order 1/b/sem

clean2:
	rm -f 2/run
	rm -f 2/fifo/client 2/fifo/server
	rm -f 2/shm/client 2/shm/server
	rm -f 2/sockets/client 2/sockets/server

clean3:
	rm -f 3/main
	cd 3 && make clean