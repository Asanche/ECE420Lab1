#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab1_IO.h"
#include "timer.h"


int** matrix_a, matrix_b;
int size;

void* threadfunc (void* arg_p)
{
    
} 

int main (int argc, char* argv[])
{
    //todo: error handling for input
    int thread_count = strtol(argv[1], NULL, 10);
    pthread_t* thread_handles = malloc(thread_count*sizeof(pthread_t));

    Lab1_loadinput(&matrix_a, &matrix_b, &size);

    for(int i = 0; i < size){
        for(long thread = 0; thread < thread_count; thread++){
            pthread_create(&thread_handles[thread], NULL, threadfunc, (void*)thread);
            i++
        }
    
        for(long thread = 0; thread < thread_count; thread++){
            pthread_join(thread_handles[thread], NULL);
        }
    }
}



