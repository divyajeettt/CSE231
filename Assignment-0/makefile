all: assemble compile

assemble:
	yasm -f elf64 -o divyajeet_2021529.o divyajeet_2021529.asm

compile:
	gcc -o divyajeet_2021529 divyajeet_2021529.o -no-pie

clean:
	rm divyajeet_2021529.o
