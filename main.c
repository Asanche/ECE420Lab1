#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab1_IO.h"
#include "timer.h"


int** matrix_a; int** matrix_b; int**matrix_c;
int size;

void* Calculate_element (void* arg_p)
{
    long outputSpot = (long) arg_p;
    long x = outputSpot % size;
    long y = outputSpot / size;
    long sum = 0;
    for (int i = 0; i < size; i++){
        sum += matrix_a[x][i] * matrix_b[i][y];
    }
    matrix_c[x][y] = sum;
    return NULL;
} 

int main (int argc, char* argv[])
{
    double start; double end;
    int thread_count = strtol(argv[1], NULL, 10);
    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t));

    Lab1_loadinput(&matrix_a, &matrix_b, &size);

    matrix_c = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
      matrix_c[i] = malloc(size * sizeof(int));
    }

    GET_TIME(start);
    for(long i = 0; i < size * size;){
        for(long thread = 0; thread < thread_count; thread++){
            pthread_create(&thread_handles[thread], NULL, Calculate_element, (void*)i);
            i++;
        }
    
        for(long thread = 0; thread < thread_count; thread++){
            pthread_join(thread_handles[thread], NULL);
        }
    }
    GET_TIME(end);

    Lab1_saveoutput(matrix_c, &size, end-start);
}



