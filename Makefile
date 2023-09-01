bin: main.o asm.o
	gcc main.o asm.o -o bin

main.o: main.c
	gcc -c main.c -o main.o

asm.o: main.asm
	as main.asm -o asm.o
