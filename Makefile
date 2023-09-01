bin: main.o asm.o
	clang main.o asm.o -g -o bin

main.o: main.c
	clang -c main.c -g -o main.o

asm.o: main.asm
	as main.asm -g -o asm.o

clean:
	rm *.o
	rm bin
