bin: main.o asm.o
	@clang main.o asm.o -g -o bin

main.o: main.c
	@clang -c main.c -O3 -g -o main.o

main.preprocessed: main.asm
	@sed 's/;/#/g' main.asm > main.preprocessed

asm.o: main.preprocessed
	@as main.preprocessed -g -o asm.o

clean:
	@rm *.o bin *.preprocessed
