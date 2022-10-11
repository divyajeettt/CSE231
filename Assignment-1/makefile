all: compile

compile:
	gcc ./src/main.c -o ./bin/main.out
	gcc ./src/cat.c -o ./bin/cat.out
	gcc ./src/date.c -o ./bin/date.out
	gcc ./src/ls.c -o ./bin/ls.out
	gcc ./src/mkdir.c -o ./bin/mkdir.out
	gcc ./src/rm.c -o ./bin/rm.out

run:
	.bin/main.out

clean:
	rm -rf ./bin