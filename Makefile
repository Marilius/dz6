all: main

main: task.o functions.o
	gcc -m32 -o main task.o functions.o

functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm

task.o: task.c
	gcc -m32 -lm -c -o task.o task.c

clean:
	rm -f *.o
	rm -f main