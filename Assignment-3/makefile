all: 1a 1b

1a:
	gcc -pthread -o 1/a/1 1/a/1.c
	gcc -pthread -o 1/a/2 1/a/2.c

1b:
	gcc -pthread -o 1/b/1 1/b/1.c
	gcc -pthread -o 1/b/2 1/b/2.c

run1a1: ./1/a/1
run1a2: ./1/a/2
run1b1: ./1/b/1
run1b2: ./1/b/2

clean:
	rm -f 1/a/1 1/a/2 1/b/1 1/b/2