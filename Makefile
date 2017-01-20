compile: clean main matrixgen serialtester

clean:
	rm -rf tmp main.exe main.o matrixgen.exe matrixgen.o serialtester.exe serialtester.o data_input.txt data_output.txt 

fix:
	chmod u+x check.sh

main: main.c lab1_IO.c
	gcc -g -Wall -o main main.c lab1_IO.c -lpthread -lm

matrixgen: matrixgen.c
	gcc -g -Wall -o matrixgen matrixgen.c

serialtester: serialtester.c lab1_IO.c
	gcc -g -Wall -o serialtester serialtester.c lab1_IO.c

check:
	./check.sh

run: fix compile check 
