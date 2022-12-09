all: make1 make2 make3

make1: 1a 1b
make2: fifo shared-memory sockets
make3: thing

clean: clean1 clean2 clean3

1a:
	gcc -pthread -o 1/a/mutex 1/a/mutex.c
	gcc -pthread -o 1/a/sempahore 1/a/sempahore.c

1b:
	gcc -pthread -o 1/b/mutex 1/b/mutex.c
	gcc -pthread -o 1/b/sempahore 1/b/sempahore.c

fifo:
	gcc -o 2/run 2/run.c
	gcc -o 2/fifo/client 2/fifo/client.c
	gcc -o 2/fifo/server 2/fifo/server.c

shared-memory:
	gcc -o 2/run 2/run.c
	gcc -o 2/shared-memory/client 2/shared-memory/client.c
	gcc -o 2/shared-memory/server 2/shared-memory/server.c

sockets:
	gcc -o 2/run 2/run.c
	gcc -o 2/sockets/client 2/sockets/client.c
	gcc -o 2/sockets/server 2/sockets/server.c

# thing:

run1a1:
	./1/a/1
run1a2:
	./1/a/2
run1b1:
	./1/b/1
run1b2:
	./1/b/2

run2fifo:
	./2/run fifo
run2shared-memory:
	./2/run shared-memory
run2sockets:
	./2/run sockets

clean1:
	rm -f 1/a/1 1/a/2
	rm -f 1/b/1 1/b/2

clean2:
	rm -f 2/run
	rm -f 2/fifo/client 2/fifo/server
	rm -f 2/shared-memory/client 2/shared-memory/server
	rm -f 2/sockets/client 2/sockets/server

clean3:
	rm -f 3/main