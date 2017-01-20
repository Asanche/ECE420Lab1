#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab1_IO.h"
#include "timer.h"


int** matrix_a; int** matrix_b; int**matrix_c;
int size;

void* Calculate_element (void* arg_p)
{
    long element_index = (long) arg_p;
    long x = element_index % size;
    long y = element_index / size;
    matrix_c[x][y] = 0;
    
    for (int i = 0; i < size; i++)
    {
        matrix_c[x][y] += matrix_a[x][i] * matrix_b[i][y];
    }
    pthread_exit(NULL);
} 

int main (int argc, char* argv[])
{
    if(argv[1] == NULL || "")
    {
        printf("You didn't input a number of threads... please rerun like \"./main <threads>\"");
        return 1;
    }

    double start; double end;
    int thread_count = strtol(argv[1], NULL, 10);
    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t));

    Lab1_loadinput(&matrix_a, &matrix_b, &size);

    matrix_c = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
      matrix_c[i] = malloc(size * sizeof(int));
    }

    int area = size * size;

    GET_TIME(start);
    for(long i = 0; i < area;){
        for(long thread = 0; thread < thread_count; thread++)
        {
            pthread_create(&thread_handles[thread], NULL, Calculate_element, (void*)i);
            i++;
        }
    
        for(long thread = 0; thread < thread_count; thread++)
        {
            pthread_join(thread_handles[thread], NULL);
        }
    }
    GET_TIME(end);

    Lab1_saveoutput(matrix_c, &size, end-start);
    pthread_exit(NULL);
}



