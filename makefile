default: main

CC = gcc
CFLAGS = -Wall -O3
CORDIC_DIR = ./include/libs/Cordic/
main.exe = ./build/main.exe
testbench.exe = ./build/testbench
cordic.o:
	$(CC) $(CFLAGS) -c $(CORDIC_DIR)Cordic.c -o ./bin/cordic.o

main.o: $(CORDIC_DIR)Cordic.h
	$(CC) $(CFLAGS) -c ./src/main.c -o ./bin/main.o

main: cordic.o main.o
	$(CC) -O3 ./bin/main.o ./bin/cordic.o -o $(main.exe)
	$(main.exe)

build_testbench:
	gcc ./src/testbench.c -o $(testbench.exe) -lm
	$(testbench.exe)

