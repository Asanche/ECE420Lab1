#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lab1_IO.h"
#include "timer.h"


int** matrix_a; int** matrix_b; int**matrix_c;
int size;

void* threadfunc (void* arg_p)
{
    long outputSpot = (long) arg_p;
    long x = outputSpot%size;
    long y = floor(outputSpot/size);
    long sum = 0;
    for (int i = 0; i < size; i++){
        sum += matrix_a[x][i] * matrix_b[i][y];
    }
    matrix_c[x][y] = sum;
    return NULL;
} 

int main (int argc, char* argv[])
{
    //todo: error handling for input
    int thread_count = strtol(argv[1], NULL, 10);
    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t));

    Lab1_loadinput(&matrix_a, &matrix_b, &size);
    matrix_c = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
    {
      matrix_c[i] = malloc(size * sizeof(int));
    }
    double start; double end;
    GET_TIME(start);
    for(long i = 0; i < pow(size,2);){
        for(long thread = 0; thread < thread_count; thread++){
            pthread_create(&thread_handles[thread], NULL, threadfunc, (void*)i);
            i++;
        }
    
        for(long thread = 0; thread < thread_count; thread++){
            pthread_join(thread_handles[thread], NULL);
        }
    }
    GET_TIME(end);
    Lab1_saveoutput(matrix_c, &size, end-start);
}



