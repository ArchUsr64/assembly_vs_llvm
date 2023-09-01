bin: main.o asm.o
	clang main.o asm.o -o bin

main.o: main.c
	clang -c main.c -o main.o

asm.o: main.asm
	as main.asm -o asm.o
