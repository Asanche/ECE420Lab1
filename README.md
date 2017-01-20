# ECE420Lab1
Code for ECE 420 Lab 1

##Simple Run Instructions:
* Run "make" to compile, or "make run" to compile and run the check

## Make Command List:

clean:
* removes tmp/, main.exe, main.o, matrixgen.exe, matrixgen.o, serialtester.exe, serialtester.o, data_input.txt, data_output.txt,

fix:
* changes the permissions for check.sh to include u+x

main:
* compiles main.c and lab1_IO.c main.o or main.exe (cygwin)

serialchecker:
* compiles serialchecker and lab1_IO.c serialchecker.o or serialchecker.exe (cygwin)

matrixgen:
* compiles matrixgen.c with output matrixgen.o or matrixgen.exe (cygwin)

compile:
* runs clean, main, matrixgen, and serialchecker

check:
* runs "./check.sh"

run:
* runs compile, fix, and check