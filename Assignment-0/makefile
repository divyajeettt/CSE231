all: assemble compile

assemble:
	yasm -f elf64 -o main.o main.asm

compile:
	gcc -o main main.o -no-pie

clean:
	rm main.o
