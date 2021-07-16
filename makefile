default: main

CC = gcc
ARMCC = arm-none-eabi-gcc
SCH_ARMCC = arm-linux-gcc

CFLAGS = -Wall -O3
CORDIC_DIR = ./include/libs/Cordic/
main.exe = ./build/main.exe
arm-main.exe = ./build/main.exe
testbench.exe = ./build/testbench

cordic.o:
	$(CC) $(CFLAGS) -c $(CORDIC_DIR)Cordic.c -o ./bin/cordic.o

main.o: $(CORDIC_DIR)Cordic.h
	$(CC) $(CFLAGS) -c ./src/main.c -o ./bin/main.o

main: cordic.o main.o
	$(CC) -O3 -pg ./bin/main.o ./bin/cordic.o -o $(main.exe)
	$(main.exe) 0.85, 0.76, 0

build_testbench:
	gcc ./src/testbench.c -o $(testbench.exe) -lm
	$(testbench.exe)

arm-cordic.o:
	$(ARMCC) $(CFLAGS) -c $(CORDIC_DIR)Cordic.c -o ./bin/arm-cordic.o
arm-main.o:
	$(ARMCC) $(CFLAGS) -c ./src/main.c -o ./bin/arm-main.o
arm_main: arm-cordic.o arm-main.o
	$(ARMCC) -pg --specs=rdimon.specs -O3 ./bin/arm-main.o ./bin/arm-cordic.o -o $(arm-main.exe)

school-arm-cordic.o:
	$(SCH_ARMCC) $(CFLAGS) -c $(CORDIC_DIR)Cordic.c -o ./bin/arm-cordic.o

school-arm-main.o:
	$(SCH_ARMCC) $(CFLAGS) -c ./src/main.c -o ./bin/arm-main.o
school-arm-main: school-arm-cordic.o school-arm-main.o
	$(SCH_ARMCC) -pg --specs=rdimon.specs -O3 ./bin/arm-main.o ./bin/arm-cordic.o -o $(arm-main.exe)