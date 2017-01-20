all: main matrixgen serialtester

main: main.c lab1_IO.c
	gcc -g -Wall -o main main.c lab1_IO.c -lpthread

matrixgen: matrixgen.c
	gcc -g -Wall -o matrixgen matrixgen.c

serialtester: serialtester.c lab1_IO.c
	gcc -g -Wall -o serialtester serialtester.c lab1_IO.c