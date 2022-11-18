all: 1.1 1.2 test
clean: clean1.2 cleanbin

1.1:
	gcc -pthread -o ./1/1.1/main ./1/1.1/main.c

1.2:
	gcc -o ./1/1.2/main ./1/1.2/main.c

test:
	gcc -o ./2/test ./2/test.c

run1.1:
	sudo ./1/1.1/main

run1.2:
	mkdir -p ./kernelbuildA
	mkdir -p ./kernelbuildB
	mkdir -p ./kernelbuildC
	sudo ./1/1.2/main

test2:
	./2/test

clean1.2:
	sudo rm -rf ./kernelbuildA
	sudo rm -rf ./kernelbuildB
	sudo rm -rf ./kernelbuildC

cleanbin:
	rm -f ./1/1.1/main
	rm -f ./1/1.2/main
	rm -f ./2/test